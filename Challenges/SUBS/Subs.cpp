//
// Created by Elmar Hinz on 20.08.17.
//

#include <vector>
#include "Subs.h"

void Subs::build() {
    auto lines = to_lines(input);
    model["strand"] = lines[0];
    model["motif"] = lines[1];
}

void Subs::calc() {
    result = positions(model["strand"], model["motif"]);
}

void Subs::format() {
    for(auto item : result) {
        output += std::to_string(item) + " ";
    }
    output.pop_back();
}

std::vector<unsigned> Subs::positions(std::string strand, std::string motif) {
    std::vector<unsigned int> result;
    auto pos = strand.find(motif);
    while(std::string::npos != pos) {
        pos++;
        result.emplace_back(pos);
        pos = strand.find(motif, pos);
    }
    return result;
}
