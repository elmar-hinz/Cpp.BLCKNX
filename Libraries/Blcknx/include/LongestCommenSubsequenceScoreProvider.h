//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_LONGESTCOMMENSUBSEQUENCESCOREPROVIDER_H
#define BLCKNX_LONGESTCOMMENSUBSEQUENCESCOREPROVIDER_H

#include "AlignmentScoreProviderInterface.h"

namespace blcknx {

    class LongestCommenSubsequenceScoreProvider
            : public AlignmentScoreProviderInterface {

    public:
        int getScore(char deletion, char insertion) override;

        int getDeletionScore(char deletion) override;

        int getInsertionScore(char insertion) override;

    };

}


#endif //BLCKNX_LONGESTCOMMENSUBSEQUENCESCOREPROVIDER_H
