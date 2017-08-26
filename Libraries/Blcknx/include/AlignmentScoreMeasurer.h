//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_ALIGNMENTSCOREMEASURER_H
#define BLCKNX_ALIGNMENTSCOREMEASURER_H

#include <vector>
#include <string>
#include "AlignmentScoreProviderInterface.h"

namespace blcknx {
    class AlignmentScoreMeasurer {
    public:
        void setScoreProvider(AlignmentScoreProviderInterface *provider);

        AlignmentScoreProviderInterface *getScoreProvider() const;

        void enableFreeRides();

        void disableFreeRides();

        bool hasFreeRides() const;

        void setStrand1(std::string strand1);

        void setStrand2(std::string strand2);

        std::string getStrand1() const;

        std::string getStrand2() const;

        std::vector<long> getFront() const;

        long getScore() const;


        void measure();

        long measure(std::string strand1, std::string strand2); // Returns score

        struct BestScore {
            long score;
            unsigned long index1;
            unsigned long index2;
        };

        BestScore getBestScore() const;

    protected:
        AlignmentScoreProviderInterface *provider;
        bool freeRides = false;
        std::string strand1;
        std::string strand2;
        BestScore bestScore;
        std::vector<long> front;

    };
}

#endif //BLCKNX_ALIGNMENTSCOREMEASURER_H
