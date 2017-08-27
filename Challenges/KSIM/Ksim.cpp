//
// Created by Elmar Hinz on 2017-08-27 15:34:59.888317.
//

#include <sstream>
#include <Aligner.h>
#include "Ksim.h"

namespace blcknx {

    Ksim::Ksim() {
        measurer.setScoreProvider(&provider);
    }

    void Ksim::build() {
        auto lines = to_lines(input);
        model = {static_cast<unsigned int>(stoi(lines[0])), lines[1], lines[2]};
    }

    void Ksim::calc() {
        result = find_pairs(model, find_ends(model));
        for (int i = 0; i < result.size(); ++i) { result[i].first += 1; }
        std::sort(result.begin(), result.end());
    }

    void Ksim::format() {
        std::stringstream out;
        for (auto line : result) {
            out << line.first << " " << line.second << std::endl;
        }
        output = out.str().substr(0, out.str().size() - 1);
    }

    std::vector<unsigned long> Ksim::find_ends(Ksim::Model model) {
        measurer.setFreeRideDimensions(measurer.HalfFreeRides);
        measurer.setStrand1(model.strand);
        measurer.setStrand2(model.motif);
        measurer.measure();
        auto front = measurer.getFront();
        std::vector<unsigned long> results;
        for (unsigned long index = 0; index < front.size(); index++) {
            if (front[index] >= -(long) model.distance) {
                results.push_back(index);
            }
        }
        return results;
    }

    std::vector<std::pair<unsigned long, unsigned long>>
    Ksim::find_pairs(Ksim::Model model, std::vector<unsigned long> ends) {
        std::vector<std::pair<unsigned long, unsigned long>> pairs;
        measurer.setStrand2(reversed(model.motif));
        measurer.setFreeRideDimensions(measurer.NoFreeRides);
        for (auto end : reversed(ends)) {
            auto maxlength = model.distance + model.motif.size();
            maxlength = maxlength > end ? end : maxlength;
            measurer.setStrand1(
                    reversed(model.strand.substr(end - maxlength, maxlength)));
            measurer.measure();
            auto front = measurer.getFront();
            for (unsigned long index = 0; index < front.size(); index++) {
                if (front[index] >= -(long) model.distance) {
                    std::pair<unsigned long, unsigned long> pair(end - index, index);
                    pairs.push_back(pair);
                }
            }
        }
        return pairs;
    }

    template<typename T>
    T Ksim::reversed(T copy) {
        std::reverse(copy.begin(), copy.end());
        return copy;
    }

}