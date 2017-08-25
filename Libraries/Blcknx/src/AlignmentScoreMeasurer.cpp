//
// Created by Elmar Hinz on 23.08.17.
//

#include "AlignmentScoreMeasurer.h"
#include <numeric>
#include <iostream>
#include <sstream>

namespace blcknx {

    void AlignmentScoreMeasurer::setScoreProvider(
            AlignmentScoreProviderInterface *provider) {
        this->provider = provider;
    }

    void AlignmentScoreMeasurer::enableMatrix() {
        matrixPointer = &matrix;
    }

    void AlignmentScoreMeasurer::disableMatrix() {
        matrixPointer = 0;
    }

    bool AlignmentScoreMeasurer::hasMatrix() {
        return static_cast<bool>(matrixPointer);
    }

    void AlignmentScoreMeasurer::enableFreeRides() {
        freeRides = true;
    }

    void AlignmentScoreMeasurer::disableFreeRides() {
        freeRides = false;
    }

    bool AlignmentScoreMeasurer::hasFreeRides() {
        return freeRides;
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

    std::string AlignmentScoreMeasurer::getStrand1() {
        return strand1;
    }

    std::string AlignmentScoreMeasurer::getStrand2() {
        return strand2;
    }

    long AlignmentScoreMeasurer::getScore() {
        return front.back();
    }

    std::vector<long> AlignmentScoreMeasurer::getFront() {
        return front;
    }

    void AlignmentScoreMeasurer::setupMatrix() {
        auto d1 = strand1.size() + 1;
        auto d2 = strand2.size() + 1;
        matrix = std::vector<std::vector<MatrixCell>>(
                d1, std::vector<MatrixCell>(d2));
    }

    void AlignmentScoreMeasurer::measure() {
        char char1, char2;
        long deletion, insertion, match, best;
        unsigned long index1, index2;
        std::vector<long> last(strand1.size() + 1);
        std::vector<long> current(strand1.size() + 1);
        last[0] = 0;
        if (hasMatrix()) {
            setupMatrix();
            matrix[0][0].address = {0, 0};
            matrix[0][0].backPointer = {0, 0};
            matrix[0][0].score = 0;

        }
        for (index1 = 1; index1 <= strand1.size(); ++index1) {
            char1 = strand1[index1 - 1];
            best = last[index1 - 1] + provider->getDeletionScore(char1);
            if (hasFreeRides() && best < 0) { best = 0; }
            last[index1] = best;
            if (hasMatrix()) {
                matrix[index1][0].address = {index1, 0};
                if (best == 0) {
                    matrix[index1][0].backPointer = {0, 0};
                } else {
                    matrix[index1][0].backPointer = {index1, index1 - 1};
                }
                matrix[index1][0].score = best;
            }
        }
        for (index2 = 1; index2 <= strand2.size(); ++index2) {
            char2 = strand2[index2 - 1];
            current[0] = last[0] + provider->getInsertionScore(char2);
            for (index1 = 1; index1 <= strand1.size(); ++index1) {
                char1 = strand1[index1 - 1];
                deletion = current[index1 - 1] +
                           provider->getDeletionScore(char2);
                insertion =
                        last[index1] + provider->getInsertionScore(char2);
                best = std::max(insertion, deletion);
                match = last[index1 - 1] + provider->getScore(char1, char2);
                best = std::max(best, match);
                if (hasFreeRides() && best < 0) { best = 0; }
                current[index1] = best;
                if (hasMatrix()) {
                    matrix[index1][index2].address = {index1, index2};
                    if (best == 0) {
                        matrix[index1][index2].backPointer = {0, 0};
                    } else if (match == best) {
                        matrix[index1][index2].backPointer = {index1 - 1,
                                                              index2 - 1};
                    } else if (deletion == best) {
                        matrix[index1][index2].backPointer =
                                {index1 - 1, index2};
                    } else if (insertion == best) {
                        matrix[index1][index2].backPointer =
                                {index1, index2 - 1};
                    }
                    matrix[index1][index2].score = best;
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

    AlignmentScoreMeasurer::MatrixCell
    AlignmentScoreMeasurer::findMatrixWinner() {
        MatrixCell winner = matrix[matrix.size() - 1][matrix[0].size() - 1];
        for (auto row : matrix) {
            for (auto cell : row) {
                if (cell.score >= winner.score) { winner = cell; }
            }
        }
        return winner;
    }

    AlignmentScoreMeasurer::Backtracks
    AlignmentScoreMeasurer::backtrack(MatrixCell endPoint) {
        auto current = endPoint;
        Backtracks backtracks{};
        while (true) {
            if (current == matrix[0][0]) { break; }
            if (hasFreeRides()
                && current.backPointer.first == 0
                && current.backPointer.second == 0
                && !neighboursOrigin(current)) {
                break;
            }
            auto address = current.address;
            auto pointer = current.backPointer;
            char c1 = strand1[pointer.first];
            char c2 = strand2[pointer.second];
            if (address.first == pointer.first) {
                // Insertion
                backtracks.alignment1 = "-" + backtracks.alignment1;
                backtracks.alignment2 = c2 + backtracks.alignment2;
                backtracks.strand2 = c2 + backtracks.strand2;
            } else if (address.second == pointer.second) {
                // Deletion
                backtracks.alignment1 = c1 + backtracks.alignment1;
                backtracks.alignment2 = "-" + backtracks.alignment2;
                backtracks.strand1 = c1 + backtracks.strand1;
            } else if (c1 == c2) {
                // Match
                backtracks.common = c1 + backtracks.common;
                backtracks.alignment1 = c1 + backtracks.alignment1;
                backtracks.alignment2 = c2 + backtracks.alignment2;
                backtracks.strand1 = c1 + backtracks.strand1;
                backtracks.strand2 = c2 + backtracks.strand2;
            } else {
                // Substitution
                backtracks.alignment1 = c1 + backtracks.alignment1;
                backtracks.alignment2 = c2 + backtracks.alignment2;
                backtracks.strand1 = c1 + backtracks.strand1;
                backtracks.strand2 = c2 + backtracks.strand2;
            }
            current = matrix[pointer.first][pointer.second];
        }
        return backtracks;
    }

    std::string AlignmentScoreMeasurer::debugMatrix() {
        std::stringstream out;
        if (!hasMatrix()) {
            out << "Matrix disabled" << std::endl;
        } else {
            for (auto row : matrix) {
                for (auto cell : row) {
                    out << cell.score << " ";
                }
                out << std::endl;
            }
        }
        return out.str();
    }

    std::string AlignmentScoreMeasurer::debugMatrixCell(MatrixCell cell) {
        std::stringstream out;
        out << std::endl;
        out << cell.score << ": ";
        out << cell.address.first << "," << cell.address.second << " -> ";
        out << cell.backPointer.first << "," << cell.backPointer.second << " ";
        return out.str();
    }

    bool AlignmentScoreMeasurer::neighboursOrigin(
            AlignmentScoreMeasurer::MatrixCell cell) {
        bool result = false;
        if (cell.address.first == 0 && cell.address.second == 1) {
            result = true;
        } else if (cell.address.first == 1 && cell.address.second == 0) {
            result = true;
        } else if (cell.address.first == 1 && cell.address.second == 1) {
            result = true;
        }
        return result;
    }

}
