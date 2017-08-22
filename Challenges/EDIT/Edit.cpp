//
// Created by Elmar Hinz on 21.08.17.
//

#include <numeric>
#include "Edit.h"

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

unsigned Edit::edit_distance(std::string strand1, std::string strand2) {
    std::vector<unsigned> current, last(strand1.size() + 1);
    std::iota(last.begin(), last.end(), 0);
    for (unsigned w = 0; w < strand2.size(); ++w) {
        current = {w + 1};
        for (unsigned h = 0; h < strand2.size(); ++h) {
            unsigned const indel = std::min(current[h], last[h + 1]) + 1;
            unsigned const match = last[h] +
                    static_cast<unsigned int>(strand1[w] != strand2[h]);
            current.push_back(std::min(indel, match));
        }
        last = current;
    }
    return current.back();
}
