//
// Created by Elmar Hinz on 21.08.17.
//

#include <numeric>
#include "Edit.h"
#include "EditDistanceScoreProvider.h"
#include "AlignmentScoreMeasurer.h"

void Edit::build() {
    std::vector<std::string> strands = fasta_strands(to_lines(input));
    model.first = strands[0];
    model.second = strands[1];
}

void Edit::calc() {
    result = edit_distance(model.first, model.second);
}

void Edit::format() {
    output = std::to_string(result);
}

unsigned Edit::edit_distance(std::string &strand1, std::string &strand2) {
    blcknx::AlignmentScoreMeasurer measurer;
    auto *evaluator = new blcknx::EditDistanceScoreProvider;
    measurer.setScoreProvider(evaluator);
    unsigned int result = static_cast<unsigned int>(
            -measurer.measure(strand1, strand2));
    delete (evaluator);
    return result;
}

