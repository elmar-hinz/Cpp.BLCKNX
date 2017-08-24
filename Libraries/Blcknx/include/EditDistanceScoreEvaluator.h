//
// Created by Elmar Hinz on 24.08.17.
//

#ifndef BLCKNX_EDITDISTANCESCOREEVALUATOR_H
#define BLCKNX_EDITDISTANCESCOREEVALUATOR_H


#include "AlignmentScoreEvaluatorInterface.h"

namespace blcknx {
    class EditDistanceScoreEvaluator : public AlignmentScoreEvaluatorInterface {
    public:
        int getScore(char deletion, char insertion) override;

        int getDeletionScore(char deletion) override;

        int getInsertionScore(char insertion) override;
    };
}


#endif //BLCKNX_EDITDISTANCESCOREEVALUATOR_H
