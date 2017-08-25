//
// Created by Elmar Hinz on 23.08.17.
//

#include "Pam250ScoreProvider.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "TableReader.h"


namespace blcknx {

    Pam250ScoreProvider::Pam250ScoreProvider() {
        gapPenalty = 0;

        std::string definition =
                "-  A  C  D  E  F  G  H  I  K  L  M  N  P  Q  R  S  T  V  W  Y\n"
                "A  2 -2  0  0 -3  1 -1 -1 -1 -2 -1  0  1  0 -2  1  1  0 -6 -3\n"
                "C -2 12 -5 -5 -4 -3 -3 -2 -5 -6 -5 -4 -3 -5 -4  0 -2 -2 -8  0\n"
                "D  0 -5  4  3 -6  1  1 -2  0 -4 -3  2 -1  2 -1  0  0 -2 -7 -4\n"
                "E  0 -5  3  4 -5  0  1 -2  0 -3 -2  1 -1  2 -1  0  0 -2 -7 -4\n"
                "F -3 -4 -6 -5  9 -5 -2  1 -5  2  0 -3 -5 -5 -4 -3 -3 -1  0  7\n"
                "G  1 -3  1  0 -5  5 -2 -3 -2 -4 -3  0  0 -1 -3  1  0 -1 -7 -5\n"
                "H -1 -3  1  1 -2 -2  6 -2  0 -2 -2  2  0  3  2 -1 -1 -2 -3  0\n"
                "I -1 -2 -2 -2  1 -3 -2  5 -2  2  2 -2 -2 -2 -2 -1  0  4 -5 -1\n"
                "K -1 -5  0  0 -5 -2  0 -2  5 -3  0  1 -1  1  3  0  0 -2 -3 -4\n"
                "L -2 -6 -4 -3  2 -4 -2  2 -3  6  4 -3 -3 -2 -3 -3 -2  2 -2 -1\n"
                "M -1 -5 -3 -2  0 -3 -2  2  0  4  6 -2 -2 -1  0 -2 -1  2 -4 -2\n"
                "N  0 -4  2  1 -3  0  2 -2  1 -3 -2  2  0  1  0  1  0 -2 -4 -2\n"
                "P  1 -3 -1 -1 -5  0  0 -2 -1 -3 -2  0  6  0  0  1  0 -1 -6 -5\n"
                "Q  0 -5  2  2 -5 -1  3 -2  1 -2 -1  1  0  4  1 -1 -1 -2 -5 -4\n"
                "R -2 -4 -1 -1 -4 -3  2 -2  3 -3  0  0  0  1  6  0 -1 -2  2 -4\n"
                "S  1  0  0  0 -3  1 -1 -1  0 -3 -2  1  1 -1  0  2  1 -1 -2 -3\n"
                "T  1 -2  0  0 -3  0 -1  0  0 -2 -1  0  0 -1 -1  1  3  0 -5 -3\n"
                "V  0 -2 -2 -2 -1 -1 -2  4 -2  2  2 -2 -1 -2 -2 -1  0  4 -6 -2\n"
                "W -6 -8 -7 -7  0 -7 -3 -5 -3 -2 -4 -4 -6 -5  2 -2 -5 -6 17  0\n"
                "Y -3  0 -4 -4  7 -5  0 -1 -4 -1 -2 -2 -5 -4 -4 -3 -3 -2  0 10";

        TableReader::read(definition, table);
    }

    void Pam250ScoreProvider::setGapPenalty(int gapPenalty) {
        this->gapPenalty = gapPenalty;
    }

    int Pam250ScoreProvider::getGapPenalty() {
        return gapPenalty;
    }

    int Pam250ScoreProvider::getScore(char deletion, char insertion) {
        return table[deletion][insertion];
    }

    int Pam250ScoreProvider::getInsertionScore(char insertion) {
        return gapPenalty;
    }

    int Pam250ScoreProvider::getDeletionScore(char deletion) {
        return gapPenalty;
    }


}
