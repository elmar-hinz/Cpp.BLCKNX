//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_LONGESTCOMMENSUBSEQUENCESCOREEVALUATOR_H
#define BLCKNX_LONGESTCOMMENSUBSEQUENCESCOREEVALUATOR_H

#include "AlignmentScoreEvaluatorInterface.h"

namespace blcknx {

    class LongestCommenSubsequenceScoreEvaluator
            : public AlignmentScoreEvaluatorInterface {

    public:
        int getScore(char deletion, char insertion) override;

        int getDeletionScore(char deletion) override;

        int getInsertionScore(char insertion) override;

    };

}


#endif //BLCKNX_LONGESTCOMMENSUBSEQUENCESCOREEVALUATOR_H
