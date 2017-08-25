//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_BLOSUM62SCOREEVALUATOR_H
#define BLCKNX_BLOSUM62SCOREEVALUATOR_H

#include "AlignmentScoreEvaluatorInterface.h"
#include <map>
#include <string>

namespace blcknx {

    class Blosum62ScoreEvaluator : public AlignmentScoreEvaluatorInterface {
    public:
        Blosum62ScoreEvaluator();

        int getScore(char deletion, char insertion) override;

        int getInsertionScore(char insertion) override;

        int getDeletionScore(char deletion) override;

        int getGapPenalty();

        void setGapPenalty(int gapPenalty);

    protected:
        int gapPenalty;

        std::map<char, std::map<char, int>> table;
    };
}

#endif //BLCKNX_BLOSUM62SCOREEVALUATOR_H
