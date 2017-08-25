//
// Created by Elmar Hinz on 24.08.17.
//

#include "EditDistanceScoreProvider.h"

int
blcknx::EditDistanceScoreProvider::getScore(char deletion, char insertion) {
    if (deletion == insertion) {
        return 0;
    } else {
        return -1;
    }
}

int blcknx::EditDistanceScoreProvider::getDeletionScore(char deletion) {
    return -1;
}

int blcknx::EditDistanceScoreProvider::getInsertionScore(char insertion) {
    return -1;
}
