//
// Created by Elmar Hinz on 2017-08-22 13:05:12.113478.
//

#include "Edta.h"
#include "Aligner.h"

namespace blcknx {
    void Edta::build() {
        model = fasta_strands(to_lines(input));
    }

    void Edta::calc() {
        Aligner aligner;
        aligner.setScoreProvider(&provider);
        aligner.setStrand1(model[0]);
        aligner.setStrand2(model[1]);
        aligner.run();
        result = aligner.getAlignment();
    }

    void Edta::format() {
        output += std::to_string(-result.getScore()) + "\n";
        output += result.getAlignment1() + "\n";
        output += result.getAlignment2();
    }

}
