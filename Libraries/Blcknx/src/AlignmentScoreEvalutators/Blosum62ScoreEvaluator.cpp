//
// Created by Elmar Hinz on 23.08.17.
//

#include "Blosum62ScoreEvaluator.h"
#include <vector>
#include <sstream>

int blcknx::Blosum62ScoreEvaluator::getScore(char deletion, char insertion) {
    return table[deletion][insertion];
}

int blcknx::Blosum62ScoreEvaluator::getGapPenalty() {
    return gapPenalty;
}

void blcknx::Blosum62ScoreEvaluator::setGapPenalty(int gapPenalty) {
    this->gapPenalty = gapPenalty;
}

blcknx::Blosum62ScoreEvaluator::Blosum62ScoreEvaluator() {
    std::stringstream rows(definition);
    std::vector<char> header;
    std::string row;

    // Read header
    char key;
    std::getline(rows, row, '\n');
    std::stringstream ss(row);
    ss >> key; // discard vertical index
    while (ss >> key) { header.push_back(key); }

    // Read lines
    std::string cell;
    int i = 0;
    int j = 0;
    while (std::getline(rows, row, '\n')) {
        std::stringstream ssr(row);
        std::getline(ssr, cell, ' '); // discard vertical index
        while (ssr >> cell) {
            table[header[i]][header[j]] = std::stoi(cell);
            table[header[j]][header[i]] = std::stoi(cell);
            j++;
        }
        i++;
    }
}

int blcknx::Blosum62ScoreEvaluator::getInsertionScore(char insertion) {
    return gapPenalty;
}

int blcknx::Blosum62ScoreEvaluator::getDeletionScore(char deletion) {
    return gapPenalty;
}


