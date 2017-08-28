//
// Created by Elmar Hinz on 23.08.17.
//

#include "AlignmentScoreMeasurer.h"
#include <numeric>
#include <iostream>

namespace blcknx {

    void AlignmentScoreMeasurer::setFreeRideDimensions(
            AlignmentScoreMeasurer::FreeRideDimensions dimension) {
        freeRidesDimensions = dimension;
    }

    AlignmentScoreMeasurer::FreeRideDimensions
    AlignmentScoreMeasurer::getFreeRideDimensions() {
        return freeRidesDimensions;
    }

    void AlignmentScoreMeasurer::setScoreProvider(
            AlignmentScoreProviderInterface *provider) {
        this->provider = provider;
    }

    AlignmentScoreProviderInterface *
    AlignmentScoreMeasurer::getScoreProvider() const {
        return provider;
    }

    void AlignmentScoreMeasurer::setStrand1(std::string strand1) {
        this->strand1 = std::move(strand1);
    }

    void AlignmentScoreMeasurer::setStrand2(std::string strand2) {
        this->strand2 = std::move(strand2);
    }

    std::string AlignmentScoreMeasurer::getStrand1() const {
        return strand1;
    }

    std::string AlignmentScoreMeasurer::getStrand2() const {
        return strand2;
    }

    long AlignmentScoreMeasurer::getScore() const {
        return front.back();
    }

    std::vector<long> AlignmentScoreMeasurer::getFront() const {
        return front;
    }

    void AlignmentScoreMeasurer::measure() {
        std::vector<long> front(strand1.size() + 1);
        front[0] = 0;
        bestScore = {0, 0, 0};
        for (unsigned long index1 = 1; index1 <= strand1.size(); ++index1) {
            char char1 = strand1[index1 - 1];
            long best = front[index1 - 1]
                        + provider->getDeletionScore(char1);
            if (freeRidesDimensions == HalfFreeRides or
                freeRidesDimensions == FullFreeRides) {
                best = std::max(best, (long) 0);
            }
            front[index1] = best;
            if (best > bestScore.score) { bestScore = {best, index1, 0}; }
        }
        for (unsigned long index2 = 1; index2 <= strand2.size(); ++index2) {
            char char1 = strand2[index2 - 1];
            long backup = front[0];
            front[0] = front[0] + provider->getInsertionScore(char1);
            for (unsigned long index1 = 1; index1 <= strand1.size(); ++index1) {
                char char2 = strand1[index1 - 1];
                long deletion =
                        front[index1 - 1] + provider->getDeletionScore(char2);
                long insertion =
                        front[index1] + provider->getInsertionScore(char1);
                long indel = std::max(insertion, deletion);
                long match = backup + provider->getScore(char1, char2);
                long best = std::max(indel, match);
                if (freeRidesDimensions == FullFreeRides) {
                    best = std::max(best, (long) 0);
                }
                backup = front[index1];
                front[index1] = best;
                if (best > bestScore.score) {
                    bestScore = {best, index1, index2};
                }
            }
        }
        this->front = front;
    }

    long AlignmentScoreMeasurer::measure(
            std::string strand1,
            std::string strand2
    ) {
        setStrand1(std::move(strand1));
        setStrand2(std::move(strand2));
        measure();
        return getScore();
    }

    AlignmentScoreMeasurer::BestScore
    AlignmentScoreMeasurer::getBestScore() const {
        return bestScore;
    }

}
