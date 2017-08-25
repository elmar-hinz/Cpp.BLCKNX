//
// Created by Elmar Hinz on 22.08.17.
//

#include <utility>
#include <vector>
#include <numeric>
#include "Aligner.h"
#include "AlignmentScoreMeasurer.h"

namespace blcknx {
    void Aligner::setScoreProvider(
            AlignmentScoreProviderInterface *scoreProvider
    ) {
        this->scoreProvider = scoreProvider;
    }

    const std::string &Aligner::getStrand1() const {
        return strand1;
    }

    void Aligner::setStrand1(const std::string &strand1) {
        this->strand1 = strand1;
    }

    const std::string &Aligner::getStrand2() const {
        return strand2;
    }

    void Aligner::setStrand2(const std::string &strand2) {
        this->strand2 = strand2;
    }

    void Aligner::run() {
        Alignment alignment = align(strand1, strand2);
        alignment1 = alignment.strand1;
        alignment2 = alignment.strand2;
        alignmentLength = alignment1.size();
        alignmentDistance = alignment.distance;
    }

    const std::string &Aligner::getAlignment1() const {
        return alignment1;
    }

    const std::string &Aligner::getAlignment2() const {
        return alignment2;
    }

    long Aligner::getAlignmentDistance() const {
        return alignmentDistance;
    }

    long Aligner::getAlignmentLength() const {
        return alignmentLength;
    }

    Aligner::Alignment Aligner::align(
            std::string strand1, std::string strand2
    ) {

        // Initialize
        if (strand1.empty()) {
            return {0, std::string(strand2.size(), '-'), strand2};
        }
        if (strand2.empty()) {
            return {0, strand1, std::string(strand1.size(), '-')};
        }

        // Split
        Splitting splitting = split(strand2);

        // Meet in the middle
        std::vector<long> left = march(strand1, splitting.prefix);
        std::vector<long> right = march(reversed(strand1),
                                        reversed(splitting.suffix));
        Meeting meeting = meet(left, reversed(right), strand1,
                               splitting.splitter);

        // Divide and conquer
        Alignment left_alignment = align(meeting.prefix, splitting.prefix);
        Alignment right_alignment = align(meeting.suffix, splitting.suffix);

        // Build result
        Alignment alignment;
        alignment.distance = meeting.distance;
        alignment.strand1 = left_alignment.strand1
                            + meeting.char1
                            + right_alignment.strand1;
        alignment.strand2 = left_alignment.strand2
                            + meeting.char2
                            + right_alignment.strand2;
        return alignment;
    }

    std::vector<long> Aligner::march(
            std::string strand1,
            std::string strand2
    ) {
        AlignmentScoreMeasurer measurer;
        measurer.setScoreProvider(scoreProvider);
        measurer.setStrand1(std::move(strand1));
        measurer.setStrand2(std::move(strand2));
        measurer.measure();
        return measurer.getFront();
    }

    Aligner::Meeting Aligner::meet(
            std::vector<long> left,
            std::vector<long> right,
            std::string strand,
            char splitter
    ) {
        long total = -strand1.size() - strand2.size();
        Meeting best = {total, '-', splitter, "", ""};
        long strandSize = strand.size();
        for (unsigned long l = 0; l <= strandSize; ++l) {
            std::string prefix, suffix;
            long score;
            score = left[l] + right[l] +
                    scoreProvider->getInsertionScore(splitter);
            if (score > best.distance) {
                prefix = strand.substr(0, l);
                suffix = strand.substr(l, strandSize - l);
                best = {score, '-', splitter, prefix, suffix};
            }
            if (l > 0) {
                char del = strand[l - 1];
                score = left[l - 1] + right[l] +
                        scoreProvider->getScore(del, splitter);
                if (score > best.distance) {
                    prefix = strand.substr(0, l - 1);
                    suffix = strand.substr(l, strandSize - l);
                    best = {score, del, splitter, prefix, suffix};
                }
            }
        }
        return best;
    }

    Aligner::Splitting
    Aligner::split(std::string strand) {
        unsigned long middle = strand.size() / 2;
        Splitting splitting;
        splitting.prefix = strand.substr(0, middle);
        splitting.splitter = strand[middle];
        splitting.suffix = strand.substr(middle + 1,
                                         strand.size() - middle - 1);
        return splitting;
    }

    template<typename T>
    T Aligner::reversed(T copy) {
        std::reverse(copy.begin(), copy.end());
        return copy;
    }


}
