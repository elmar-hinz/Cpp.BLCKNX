//
// Created by Elmar Hinz on 2017-08-23 14:17:46.414158.
//

#include "Glob.h"
#include "AlignmentScoreMeasurer.h"
#include "Blosum62ScoreEvaluator.h"

namespace blcknx {

    void Glob::build() {
        std::vector<std::string> strands = fasta_strands(to_lines(input));
        model.first = strands[0];
        model.second = strands[1];
    }

    void Glob::calc() {
        AlignmentScoreMeasurer measurer;
        Blosum62ScoreEvaluator evaluator;
        evaluator.setGapPenalty(-5);
        measurer.setScoreEvaluator(&evaluator);
        result = measurer.measure(model.first, model.second);
    }

    void Glob::format() {
        output = std::to_string(result);
    }

}
