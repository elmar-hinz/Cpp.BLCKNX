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

    void Aligner::setMotifOrStrand2(const std::string &strand2) {
        alignment.setStrand2(strand2);
    }

    void Aligner::setScoreProvider(
            AlignmentScoreProviderInterface *scoreProvider
    ) {
        this->scoreProvider = scoreProvider;
    }

    void Aligner::alignGlobally() {
        alignment = align(alignment.getStrand1(), alignment.getStrand2());
        alignment.setMotifLength1(alignment.getStrand1().size());
        alignment.setMotifLength2(alignment.getStrand2().size());
    }

    void Aligner::alignLocally() {
        // TODO
    }

    void Aligner::alignFitting() {
        alignment = align(alignment.getStrand1(), alignment.getStrand2(), true,
                          true);
        alignment.setMotifLength1(alignment.getStrand1().size());
        alignment.setMotifLength2(alignment.getStrand2().size());
    }

    Alignment Aligner::align(
            const std::string &strand1,
            const std::string &strand2,
            bool freeRidesLeft,
            bool freeRidesRight
    ) {
        Alignment alignment;
        alignment.setStrand1(strand1);
        alignment.setStrand2(strand2);
        alignment.setScore(0);

        // Initialize
        if (strand2.empty()) {
            // Deletion
            long score = 0;
            std::string alignment1, alignment2;
            for (char c : strand1) {
                alignment1 += c;
                alignment2 += '-';
                score = score + scoreProvider->getDeletionScore(c);
                if (freeRidesLeft || freeRidesRight) {
                    if (score <= 0) {
                        score = 0;
                        alignment1 = "";
                        alignment2 = "";
                    }
                }
            }
            alignment.setAlignment1(alignment1);
            alignment.setAlignment2(alignment2);
            return alignment;
        }

        // Split
        Splitting splitting = split(strand2);

        // Meet in the middle
        std::vector<long> left = march(
                strand1, splitting.prefix, freeRidesLeft);
        std::vector<long> right = march(
                reversed(strand1), reversed(splitting.suffix), freeRidesRight);
        Meeting meeting = meet(left, reversed(right), strand1,
                               splitting.splitter);

        // Divide and conquer
        Alignment left_alignment = align(meeting.prefix, splitting.prefix,
                                         freeRidesLeft, false);
        Alignment right_alignment = align(meeting.suffix, splitting.suffix,
                                          false, freeRidesRight);

        // Build result
        alignment.setScore(meeting.score);
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
            const std::string &strand1,
            const std::string &strand2,
            bool zeroBorders
    ) {
        AlignmentScoreMeasurer measurer;
        if (zeroBorders) {
            measurer.setFreeRideDimensions(measurer.BorderFreeRides);
        }
        measurer.setScoreProvider(scoreProvider);
        measurer.setStrand1(strand1);
        measurer.setStrand2(strand2);
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
            if (score > best.score) {
                prefix = strand.substr(0, l);
                suffix = strand.substr(l, strandSize - l);
                best = {score, '-', splitter, prefix, suffix};
            }
            if (l > 0) {
                char del = strand[l - 1];
                score = left[l - 1] + right[l] +
                        scoreProvider->getScore(del, splitter);
                if (score > best.score) {
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
        return -alignment.getStrand1().size() - alignment.getStrand2().size();
    }

}
