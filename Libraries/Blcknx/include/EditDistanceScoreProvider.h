//
// Created by Elmar Hinz on 24.08.17.
//

#ifndef BLCKNX_EDITDISTANCESCOREPROVIDER_H
#define BLCKNX_EDITDISTANCESCOREPROVIDER_H


#include "AlignmentScoreProviderInterface.h"

namespace blcknx {
    class EditDistanceScoreProvider : public AlignmentScoreProviderInterface {
    public:
        int getScore(char deletion, char insertion) override;

        int getDeletionScore(char deletion) override;

        int getInsertionScore(char insertion) override;
    };
}


#endif //BLCKNX_EDITDISTANCESCOREPROVIDER_H
