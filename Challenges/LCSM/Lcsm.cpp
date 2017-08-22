//
// Created by Elmar Hinz on 20.08.17.
//

#include "Lcsm.h"

void Lcsm::build() {
    model = fasta_strands(to_lines(input));
}

void Lcsm::calc() {
    result = longest_common_shared_motif(model);
}

void Lcsm::format() {
    output = result;
}

/*
 * Brute force top down.
 */
std::string Lcsm::longest_common_shared_motif(std::vector<std::string> strands)
{
    std::string first = strands[0];
    for (auto l= static_cast<unsigned>(first.length() - 1); l != 0; l--) {
        for (unsigned s=0; s + l < first.length(); s++) {
            std::string candidate = first.substr(s, l);
            bool in_all = true;
            for(unsigned m=1; in_all && m < strands.size(); m++) {
                in_all = strands[m].find(candidate) != std::string::npos;
            }
            if(in_all) return candidate;
        }
    }
    return "";
}
