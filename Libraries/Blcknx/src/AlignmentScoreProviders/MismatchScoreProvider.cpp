//
// Created by Elmar Hinz on 27.08.17.
//

#include "MismatchScoreProvider.h"

int
blcknx::MismatchScoreProvider::getScore(char deletion, char insertion) {
    if (deletion == insertion) {
        return 1;
    } else {
        return -1;
    }
}

int blcknx::MismatchScoreProvider::getDeletionScore(char deletion) {
    return -1;
}

int blcknx::MismatchScoreProvider::getInsertionScore(char insertion) {
    return -1;
}

