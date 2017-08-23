//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_BLOSUM62SCOREEVALUATOR_H
#define BLCKNX_BLOSUM62SCOREEVALUATOR_H

#include "AlignmentScoreEvaluatorInterface.h"
#include <map>
#include <string>

namespace blcknx {

    class Blosum62ScoreEvaluator : AlignmentScoreEvaluatorInterface {
    public:
        Blosum62ScoreEvaluator();

        int getScore(char deletion, char insertion) override;

        int getInsertionScore(char insertion) override;

        int getDeletionScore(char deletion) override;

    protected:
        int gapPenalty = 0;
    public:
        int getGapPenalty();

        void setGapPenalty(int gapPenalty);

    protected:

        std::map<char, std::map<char, int>> table;

        std::string definition = "-  A  C  D  E  F  G  H  I  K  L  M  N  P  Q  R  S  T  V  W  Y\n"
                "A  4  0 -2 -1 -2  0 -2 -1 -1 -1 -1 -2 -1 -1 -1  1  0  0 -3 -2\n"
                "C  0  9 -3 -4 -2 -3 -3 -1 -3 -1 -1 -3 -3 -3 -3 -1 -1 -1 -2 -2\n"
                "D -2 -3  6  2 -3 -1 -1 -3 -1 -4 -3  1 -1  0 -2  0 -1 -3 -4 -3\n"
                "E -1 -4  2  5 -3 -2  0 -3  1 -3 -2  0 -1  2  0  0 -1 -2 -3 -2\n"
                "F -2 -2 -3 -3  6 -3 -1  0 -3  0  0 -3 -4 -3 -3 -2 -2 -1  1  3\n"
                "G  0 -3 -1 -2 -3  6 -2 -4 -2 -4 -3  0 -2 -2 -2  0 -2 -3 -2 -3\n"
                "H -2 -3 -1  0 -1 -2  8 -3 -1 -3 -2  1 -2  0  0 -1 -2 -3 -2  2\n"
                "I -1 -1 -3 -3  0 -4 -3  4 -3  2  1 -3 -3 -3 -3 -2 -1  3 -3 -1\n"
                "K -1 -3 -1  1 -3 -2 -1 -3  5 -2 -1  0 -1  1  2  0 -1 -2 -3 -2\n"
                "L -1 -1 -4 -3  0 -4 -3  2 -2  4  2 -3 -3 -2 -2 -2 -1  1 -2 -1\n"
                "M -1 -1 -3 -2  0 -3 -2  1 -1  2  5 -2 -2  0 -1 -1 -1  1 -1 -1\n"
                "N -2 -3  1  0 -3  0  1 -3  0 -3 -2  6 -2  0  0  1  0 -3 -4 -2\n"
                "P -1 -3 -1 -1 -4 -2 -2 -3 -1 -3 -2 -2  7 -1 -2 -1 -1 -2 -4 -3\n"
                "Q -1 -3  0  2 -3 -2  0 -3  1 -2  0  0 -1  5  1  0 -1 -2 -2 -1\n"
                "R -1 -3 -2  0 -3 -2  0 -3  2 -2 -1  0 -2  1  5 -1 -1 -3 -3 -2\n"
                "S  1 -1  0  0 -2  0 -1 -2  0 -2 -1  1 -1  0 -1  4  1 -2 -3 -2\n"
                "T  0 -1 -1 -1 -2 -2 -2 -1 -1 -1 -1  0 -1 -1 -1  1  5  0 -2 -2\n"
                "V  0 -1 -3 -2 -1 -3 -3  3 -2  1  1 -3 -2 -2 -3 -2  0  4 -3 -1\n"
                "W -3 -2 -4 -3  1 -2 -2 -3 -3 -2 -1 -4 -4 -2 -3 -3 -2 -3 11  2\n"
                "Y -2 -2 -3 -2  3 -3  2 -1 -2 -1 -1 -2 -3 -1 -2 -2 -2 -1  2  7";
    };
}

#endif //BLCKNX_BLOSUM62SCOREEVALUATOR_H
