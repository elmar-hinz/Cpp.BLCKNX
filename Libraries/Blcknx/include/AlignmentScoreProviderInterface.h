//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_ALIGNMENTSCOREPROVIDERINTERFACE_H
#define BLCKNX_ALIGNMENTSCOREPROVIDERINTERFACE_H

namespace blcknx {
    class AlignmentScoreProviderInterface {
    public:
        virtual int getScore(char deletion, char insertion) = 0;
        virtual int getDeletionScore(char deletion) = 0;
        virtual int getInsertionScore(char insertion) = 0;
    };
}

#endif //BLCKNX_ALIGNMENTSCOREPROVIDERINTERFACE_H
