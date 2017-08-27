//
// Created by Elmar Hinz on 27.08.17.
//

#ifndef BLCKNX_MISMATCHSCOREPROVIDER_H
#define BLCKNX_MISMATCHSCOREPROVIDER_H


#include "AlignmentScoreProviderInterface.h"

namespace blcknx {
    class MismatchScoreProvider : public AlignmentScoreProviderInterface{
    public:
        int getScore(char deletion, char insertion) override;

        int getDeletionScore(char deletion) override;

        int getInsertionScore(char insertion) override;
    };
}

#endif //BLCKNX_MISMATCHSCOREPROVIDER_H
