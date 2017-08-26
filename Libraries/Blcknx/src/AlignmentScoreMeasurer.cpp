//
// Created by Elmar Hinz on 23.08.17.
//

#include "AlignmentScoreMeasurer.h"
#include <numeric>

namespace blcknx {

    void AlignmentScoreMeasurer::setScoreProvider(
            AlignmentScoreProviderInterface *provider) {
        this->provider = provider;
    }

    AlignmentScoreProviderInterface *
    AlignmentScoreMeasurer::getScoreProvider() const {
        return provider;
    }

    void AlignmentScoreMeasurer::enableFreeRides() {
        freeRides = true;
    }

    void AlignmentScoreMeasurer::disableFreeRides() {
        freeRides = false;
    }

    bool AlignmentScoreMeasurer::hasFreeRides() const {
        return freeRides;
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
        std::vector<long> last(strand1.size() + 1);
        std::vector<long> current(strand1.size() + 1);
        char char1, char2;
        last[0] = 0;
        bestScore = {0, 0, 0};
        for (unsigned long index1 = 1; index1 <= strand1.size(); ++index1) {
            char1 = strand1[index1 - 1];
            long best = last[index1 - 1] + provider->getDeletionScore(char1);
            if (hasFreeRides()) { best = std::max(best, (long) 0); }
            last[index1] = best;
            if (best > bestScore.score) { bestScore = {best, index1, 0}; }
        }
        for (unsigned long index2 = 1; index2 <= strand2.size(); ++index2) {
            char1 = strand2[index2 - 1];
            current[0] = last[0] + provider->getInsertionScore(char1);
            for (unsigned long index1 = 1; index1 <= strand1.size(); ++index1) {
                char2 = strand1[index1 - 1];
                long deletion = current[index1 - 1] +
                                provider->getDeletionScore(char2);
                long insertion =
                        last[index1] + provider->getInsertionScore(char1);
                long indel = std::max(insertion, deletion);
                long s = provider->getScore(char1, char2);
                long match = last[index1 - 1] + s;
                long best = std::max(indel, match);
                if (hasFreeRides()) { best = std::max(best, (long) 0); }
                current[index1] = best;
                if (best > bestScore.score) {
                    bestScore = {best, index1, index2};
                }
            }
            last = current;
        }
        front = last;
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
