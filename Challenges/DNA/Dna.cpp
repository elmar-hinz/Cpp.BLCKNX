//
// Created by Elmar Hinz on 20.08.17.
//

#include <map>
#include "Dna.h"

void Dna::build() {
    model = to_lines(input)[0];
}

void Dna::calc() {
    result = count_nucleotides(model);
}

void Dna::format() {
    for (auto &count : result) {
        output += std::to_string(count) + ' ';
    }
}

std::vector<unsigned> Dna::count_nucleotides(std::string strand) {
    std::map<char, unsigned> counter;
    counter['A'] = 0;
    counter['C'] = 0;
    counter['G'] = 0;
    counter['T'] = 0;
    for (auto &c : strand) {
        counter[c] += 1;
    }
    std::vector<unsigned> ret;
    ret.push_back((unsigned) counter['A']);
    ret.push_back((unsigned) counter['C']);
    ret.push_back((unsigned) counter['G']);
    ret.push_back((unsigned) counter['T']);
    return ret;
}
