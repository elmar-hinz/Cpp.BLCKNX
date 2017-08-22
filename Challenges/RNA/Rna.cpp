//
// Created by Elmar Hinz on 20.08.17.
//

#include "Rna.h"

void Rna::build() {
    model = to_lines(input)[0];
}

void Rna::calc() {
    result = transcribe_dna_to_rna(model);
}

void Rna::format() {
    output = result;
}

std::string Rna::transcribe_dna_to_rna(std::string dna) {
    std::replace(dna.begin(), dna.end(), 'T', 'U');
    return dna;
}

