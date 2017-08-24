//
// Created by Elmar Hinz on 24.08.17.
//

#include "EditDistanceScoreEvaluator.h"

int
blcknx::EditDistanceScoreEvaluator::getScore(char deletion, char insertion) {
    if (deletion == insertion) {
        return 0;
    } else {
        return -1;
    }
}

int blcknx::EditDistanceScoreEvaluator::getDeletionScore(char deletion) {
    return -1;
}

int blcknx::EditDistanceScoreEvaluator::getInsertionScore(char insertion) {
    return -1;
}
