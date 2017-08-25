//
// Created by Elmar Hinz on 23.08.17.
//

#include "LongestCommenSubsequenceScoreProvider.h"

int blcknx::LongestCommenSubsequenceScoreProvider::getScore(char char1,
                                                             char char2) {
    if(char1 == char2) {
        return 1;
    } else {
        return 0;
    }
}

int blcknx::LongestCommenSubsequenceScoreProvider::getDeletionScore(
        char deletion) {
    return 0;
}

int blcknx::LongestCommenSubsequenceScoreProvider::getInsertionScore(
        char insertion) {
    return 0;
}

