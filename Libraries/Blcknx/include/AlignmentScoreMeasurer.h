//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_ALIGNMENTSCOREMEASURER_H
#define BLCKNX_ALIGNMENTSCOREMEASURER_H

#include <vector>
#include <string>

namespace blcknx {
    class AlignmentScoreProviderInterface;

    class AlignmentScoreMeasurer {
    public:
        struct MatrixCell {
            std::pair<long, long> address;
            std::pair<long, long> backPointer;
            long score;

            bool operator==(const MatrixCell &other) const {
                return (
                        score == other.score
                        && backPointer == other.backPointer
                        && address == other.address
                );
            }
        };

        struct Backtracks {
            std::string common = "";
            std::string strand1 = "";
            std::string strand2 = "";
            std::string alignment1 = "";
            std::string alignment2 = "";
        };

        void setScoreProvider(AlignmentScoreProviderInterface *provider);

        AlignmentScoreProviderInterface *getScoreProvider() const;

        void enableMatrix();

        void disableMatrix();

        bool hasMatrix();

        void enableFreeRides();

        void disableFreeRides();

        bool hasFreeRides();

        void setStrand1(std::string strand1);

        std::string getStrand1();

        void setStrand2(std::string strand2);

        std::string getStrand2();

        void measure();

        long measure(std::string strand1, std::string strand2);

        MatrixCell findMatrixWinner();

        Backtracks backtrack(MatrixCell endPoint);

        std::vector<long> getFront();

        long getScore();

        std::string debugMatrix();
        std::string debugMatrixCell(MatrixCell cell);

    protected:
        AlignmentScoreProviderInterface *provider;
        std::string strand1;
        std::string strand2;
        std::vector<long> front;
        std::vector<std::vector<MatrixCell>> matrix;
        std::vector<std::vector<MatrixCell>> *matrixPointer;
        bool freeRides = false;

        void setupMatrix();
        bool neighboursOrigin(MatrixCell cell);

    };
}

#include "AlignmentScoreProviderInterface.h"

#endif //BLCKNX_ALIGNMENTSCOREMEASURER_H
