//
// Created by Elmar Hinz on 2017-08-24 20:30:21.370680.
//

#include "Loca.h"
#include "AlignmentScoreMeasurer.h"

namespace blcknx {

    void Loca::build() {
        model = fasta_strands(to_lines(input));
    }

//    void Loca::calc() {
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
//    }

    void Loca::calc() {
        provider.setGapPenalty(-5);
        measurer.setScoreProvider(&provider);
        measurer.setFreeRideDimensions(measurer.FullFreeRides);
        unsigned long begin1, begin2, end1, end2;
        { // get best forward
            measurer.setStrand1(model[0]);
            measurer.setStrand2(model[1]);
            measurer.measure();
            AlignmentScoreMeasurer::BestScore best = measurer.getBestScore();
            result.score = best.score;
            end1 = best.index1;
            end2 = best.index2;
        }
        { // get best backwards
            measurer.setStrand1(reversed(model[0]));
            measurer.setStrand2(reversed(model[1]));
            measurer.measure();
            AlignmentScoreMeasurer::BestScore best = measurer.getBestScore();
            begin1 = model[0].size() - best.index1;
            begin2 = model[1].size() - best.index2;
        }
        { // set substrigs to result
            result.motif1 = model[0].substr(begin1, end1 - begin1);
            result.motif2 = model[1].substr(begin2, end2 - begin2);
        }

    }

    void Loca::format() {
        output += std::to_string(result.score) + "\n";
        output += result.motif1 + "\n";
        output += result.motif2;
    }

    template<typename T>
    T Loca::reversed(T copy) {
        std::reverse(copy.begin(), copy.end());
        return copy;
    }
}