//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_ALIGNMENTSCOREEVALUATORINTERFACE_H
#define BLCKNX_ALIGNMENTSCOREEVALUATORINTERFACE_H

namespace blcknx {
    class AlignmentScoreEvaluatorInterface {
    public:
        virtual int getScore(char deletion, char insertion) = 0;
        virtual int getDeletionScore(char deletion) = 0;
        virtual int getInsertionScore(char insertion) = 0;
    };
}

#endif //BLCKNX_ALIGNMENTSCOREEVALUATORINTERFACE_H
