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
//        provider.setGapPenalty(-5);
//        measurer.setScoreProvider(&provider);
//        measurer.setStrand1(model[0]);
//        measurer.setStrand2(model[1]);
//        measurer.enableMatrix();
//        measurer.enableFreeRides();
//        measurer.measure();
//        AlignmentScoreMeasurer::MatrixCell winner = measurer.findMatrixWinner();
//        AlignmentScoreMeasurer::Backtracks bt = measurer.backtrack(winner);
//        result.score = winner.score;
//        result.motif1 = bt.strand1;
//        result.motif2 = bt.strand2;

    }

    void Loca::format() {
//        output += std::to_string(result.score) + "\n";
//        output += result.motif1 + "\n";
//        output += result.motif2;
    }
    
}