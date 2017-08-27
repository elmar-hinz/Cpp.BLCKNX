//
// Created by Elmar Hinz on 2017-08-27 07:50:16.428064.
//

#include "Sims.h"

namespace blcknx {

    void Sims::build() {
        model = fasta_strands(to_lines(input));
    }

    void Sims::calc() {
        aligner.setScoreProvider(&provider);
        aligner.setStrand1(model[0]);
        aligner.setMotifOrStrand2(model[1]);
        aligner.alignFitting();
        result = aligner.getAlignment();
    }

    void Sims::format() {
        output += std::to_string(result.getScore()) + "\n";
        output += result.getAlignment1() + "\n";
        output += result.getAlignment2();
    }        
    
}