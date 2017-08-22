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
    std::vector<unsigned> current(strand1.size() + 1);
    std::iota(current.begin(), current.end(), 0);
    std::vector<unsigned> last;
    for (unsigned w = 0; w < strand2.size(); ++w) {
        last = current;
        current = {w + 1};
        for (unsigned h = 0; h < strand2.size(); ++h) {
            if (strand1[w] == strand2[h]) {
                current.push_back(last[h]);
            } else {
                unsigned cand[] = {current[h], last[h], last[h + 1]};
                current.push_back(*std::min_element(cand, cand + 3) + 1);
            }
        }
    }
    return current.back();
}
