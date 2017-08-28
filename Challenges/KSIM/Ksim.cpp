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
        std::vector<Triple> triples = find_starts(model, find_ends(model));
        result = expand_by_tolerance(model, triples);
        for (auto &r : result) { r.start += 1; }
    }

    void Ksim::format() {
        std::stringstream out;
        for (auto line : result) {
            out << line.start << " " << line.length << std::endl;
        }
        output = out.str().substr(0, out.str().size() - 1);
    }

    std::vector<unsigned long> Ksim::find_ends(Ksim::Model model) {
        measurer.setFreeRideDimensions(measurer.HalfFreeRides);
        measurer.disableFinalDeletions();
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

    std::vector<Ksim::Triple>
    Ksim::find_starts(Ksim::Model model,
                      const std::vector<unsigned long> &ends) {
        std::vector<Triple> triples;
        measurer.setStrand2(reversed(model.motif));
        measurer.setFreeRideDimensions(measurer.NoFreeRides);
        measurer.disableFinalDeletions();
        auto maxlength = model.distance + model.motif.size();
        for (auto end : reversed(ends)) {
            maxlength = maxlength > end ? end : maxlength;
            measurer.setStrand1(
                    reversed(model.strand.substr(end - maxlength, maxlength)));
            measurer.measure();
            auto front = measurer.getFront();
            for (unsigned long index = 0; index < front.size(); index++) {
                if (front[index] >= -(long) model.distance) {
                    Triple triple = {end - index, end, front[index]};
                    triples.push_back(triple);
                }
            }
        }
        return triples;
    }

    std::vector<Ksim::Result>
    Ksim::expand_by_tolerance(Ksim::Model model, std::vector<Triple> triples) {
        std::vector<Result> result;
        unsigned long strand_length = model.strand.size();
        for (auto triple : triples) {
            long excess = model.distance + triple.score;
            for (int pre = 0; pre <= excess; ++pre) {
                for (int post = 0; post <= excess - pre; ++post) {
                    long start = triple.start - pre;
                    unsigned long length =
                            pre + triple.end - triple.start + post;
                    if (start >= 0 && triple.end + post <= strand_length) {
                        Result entry = {(unsigned) start, length};
                        result.push_back(entry);
                    }
                }
            }
        }
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }

    template<typename T>
    T Ksim::reversed(T copy) {
        std::reverse(copy.begin(), copy.end());
        return copy;
    }

}