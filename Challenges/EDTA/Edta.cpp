//
// Created by Elmar Hinz on 2017-08-22 13:05:12.113478.
//

#include "Edta.h"
#include "EditDistanceAlignment.h"

void Edta::build() {
    model = fasta_strands(to_lines(input));
}

void Edta::calc() {
    result.setStrand1(model[0]);
    result.setStrand2(model[1]);
    result.run();
}

void Edta::format() {
    output += std::to_string(result.getAlignmentDistance()) + "\n";
    output += result.getAlignment1() + "\n";
    output += result.getAlignment2();
}

