//
// Created by Elmar Hinz on 23.08.17.
//

#include "LongestCommenSubsequenceScoreEvaluator.h"

int blcknx::LongestCommenSubsequenceScoreEvaluator::getScore(char char1,
                                                             char char2) {
    if(char1 == char2) {
        return 1;
    } else {
        return 0;
    }
}

int blcknx::LongestCommenSubsequenceScoreEvaluator::getDeletionScore(
        char deletion) {
    return 0;
}

int blcknx::LongestCommenSubsequenceScoreEvaluator::getInsertionScore(
        char insertion) {
    return 0;
}

