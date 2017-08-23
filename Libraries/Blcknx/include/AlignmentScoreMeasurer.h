//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_ALIGNMENTSCOREMEASURER_H
#define BLCKNX_ALIGNMENTSCOREMEASURER_H

#include <vector>
#include <string>
#include "AlignmentScoreEvaluatorInterface.h"

namespace blcknx {
    class AlignmentScoreMeasurer {
    public:
        AlignmentScoreEvaluatorInterface *getScoreEvaluator() const;

        void setScoreEvaluator(AlignmentScoreEvaluatorInterface *evaluator);

        void setStrand1(std::string strand1);

        void setStrand2(std::string strand2);

        std::string getStrand1();

        std::string getStrand2();

        std::vector<long> getFront();

        long getScore();

        void measure();

        long measure(std::string strand1, std::string strand2);

    protected:
        AlignmentScoreEvaluatorInterface *evaluator;
        std::string strand1;
        std::string strand2;
        std::vector<long> front;

    };
}

#endif //BLCKNX_ALIGNMENTSCOREMEASURER_H
