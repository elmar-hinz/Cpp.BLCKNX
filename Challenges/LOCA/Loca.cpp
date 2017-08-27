//
// Created by Elmar Hinz on 2017-08-24 20:30:21.370680.
//

#include "Loca.h"
#include "AlignmentScoreMeasurer.h"

namespace blcknx {

    void Loca::build() {
        model = fasta_strands(to_lines(input));
    }

    void Loca::calc() {
        aligner.setScoreProvider(&provider);
        provider.setGapPenalty(-5);
        aligner.setStrand1(model[0]);
        aligner.setMotifOrStrand2(model[1]);
        aligner.alignLocally();
        result = aligner.getAlignment();
    }

    void Loca::format() {
        output += std::to_string(result.getScore()) + "\n";
        output += result.getMotif1() + "\n";
        output += result.getMotif2();
    }

}