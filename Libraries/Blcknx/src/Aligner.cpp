//
// Created by Elmar Hinz on 22.08.17.
//

#include <utility>
#include <vector>
#include <numeric>
#include "Aligner.h"
#include "AlignmentScoreMeasurer.h"

namespace blcknx {

    const Alignment Aligner::getAlignment() const {
        return alignment;
    }

    void Aligner::setStrand1(const std::string &strand1) {
        alignment.setStrand1(strand1);
    }

    void Aligner::setStrand2(const std::string &strand2) {
        alignment.setStrand2(strand2);
    }

    void Aligner::setScoreProvider(
            AlignmentScoreProviderInterface *scoreProvider
    ) {
        this->scoreProvider = scoreProvider;
    }

    void Aligner::run() {
        alignment = align(alignment.getStrand1(), alignment.getStrand2());
        alignment.setMotifLength1(alignment.getStrand1().size());
        alignment.setMotifLength2(alignment.getStrand2().size());
    }

    Alignment Aligner::align(
            std::string strand1, std::string strand2
    ) {
        Alignment alignment;
        alignment.setStrand1(strand1);
        alignment.setStrand2(strand2);
        alignment.setScore(0);

        // Initialize
        if (strand1.empty()) {
            std::string alignment1(strand2.size(), '-');
            alignment.setAlignment1(alignment1);
            alignment.setAlignment2(strand2);
            return alignment;
        }
        if (strand2.empty()) {
            std::string alignment2(strand1.size(), '-');
            alignment.setAlignment1(strand1);
            alignment.setAlignment2(alignment2);
            return alignment;
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
        alignment.setScore(meeting.distance);
        alignment.setAlignment1(
                left_alignment.getAlignment1()
                + meeting.char1
                + right_alignment.getAlignment1()
        );
        alignment.setAlignment2(
                left_alignment.getAlignment2()
                + meeting.char2
                + right_alignment.getAlignment2()
        );
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
        Meeting best = {worstScore(), '-', splitter, "", ""};
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

    long Aligner::worstScore() {
        return - alignment.getStrand1().size() - alignment.getStrand2().size();
    }

}
