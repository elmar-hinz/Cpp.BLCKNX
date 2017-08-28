//
// Created by Elmar Hinz on 2017-08-27 15:34:59.888018.
//

#ifndef BLCKNX_KSIM_H
#define BLCKNX_KSIM_H

#include <Challenge.h>
#include "AlignmentScoreMeasurer.h"
#include "EditDistanceScoreProvider.h"

namespace blcknx {

    class Ksim : public Challenge {

    public:
        Ksim();

    protected:
        struct Model {
            unsigned distance;
            std::string motif;
            std::string strand;

            bool operator==(const Model &other) const {
                return (distance == other.distance
                        && motif == other.motif
                        && strand == other.strand
                );
            }
        };

        struct Triple {
            unsigned long start;
            unsigned long end;
            long score;
        };

        struct Result {
            unsigned long start;
            unsigned long length;
            bool operator<(const Result &other) const {
                return std::tie(start, length) < std::tie(other.start, other.length);
            }
            bool operator==(const Result &other) const {
                return (start == other.start && length == other.length);
            }
        };

        Model model;
        std::vector<Result> result;
        EditDistanceScoreProvider provider;
        AlignmentScoreMeasurer measurer;

        void build() override;

        void calc() override;

        void format() override;

        std::vector<unsigned long> find_ends(Model model);

        std::vector<Triple>
        find_starts(Model model, const std::vector<unsigned long> &ends);

        std::vector<Result>
        expand_by_tolerance(Model model, std::vector<Triple> triples);

        template<typename T>
        T reversed(T copy);

    };

}


#endif //BLCKNX_<built-in method upper of str object at 0x10382c298>_H