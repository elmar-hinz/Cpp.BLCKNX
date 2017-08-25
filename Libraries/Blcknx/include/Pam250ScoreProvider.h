//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_PAM250SCOREPROVIDER_H
#define BLCKNX_PAM250SCOREPROVIDER_H

#include "AlignmentScoreProviderInterface.h"
#include <map>
#include <string>

namespace blcknx {

    class Pam250ScoreProvider : public AlignmentScoreProviderInterface {
    public:
        Pam250ScoreProvider();

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

#endif //BLCKNX_PAM250SCOREPROVIDER_H
