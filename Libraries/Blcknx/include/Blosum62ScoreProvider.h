//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_BLOSUM62SCOREPROVIDER_H
#define BLCKNX_BLOSUM62SCOREPROVIDER_H

#include "AlignmentScoreProviderInterface.h"
#include <map>
#include <string>

namespace blcknx {

    class Blosum62ScoreProvider : public AlignmentScoreProviderInterface {
    public:
        Blosum62ScoreProvider();

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

#endif //BLCKNX_BLOSUM62SCOREPROVIDER_H
