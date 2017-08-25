//
// Created by Elmar Hinz on 22.08.17.
//

#ifndef BLCKNX_EDITDISTANCEALIGNMENT_H
#define BLCKNX_EDITDISTANCEALIGNMENT_H

#include <string>
#include "EditDistanceScoreProvider.h"
#include "AlignmentScoreProviderInterface.h"

namespace blcknx {
    class Aligner {
    public:
        void setScoreProvider(AlignmentScoreProviderInterface *scoreProvider);

        void setStrand1(const std::string &strand1);

        void setStrand2(const std::string &strand2);

        const std::string &getStrand1() const;

        const std::string &getStrand2() const;

        const std::string &getAlignment1() const;

        const std::string &getAlignment2() const;

        long getAlignmentDistance() const;

        long getAlignmentLength() const;

        void run();

    protected:
        std::string strand1;
        std::string strand2;
        std::string alignment1;
        std::string alignment2;
        long alignmentDistance;
        long alignmentLength;
        AlignmentScoreProviderInterface * scoreProvider;


        struct Alignment {
            long distance;
            std::string strand1;
            std::string strand2;

            bool operator==(const Alignment &other) const {
                return (distance == other.distance
                        && strand1 == other.strand1
                        && strand2 == other.strand2
                );
            }
        };

        struct Splitting {
            std::string prefix;
            char splitter;
            std::string suffix;

            bool operator==(const Splitting &other) const {
                return (prefix == other.prefix
                        && splitter == other.splitter
                        && suffix == other.suffix
                );
            }
        };

        struct Meeting {
            long distance;
            char char1;
            char char2;
            std::string prefix;
            std::string suffix;

            bool operator==(const Meeting &other) const {
                return (distance == other.distance
                        && char1 == other.char1
                        && char2 == other.char2
                        && prefix == other.prefix
                        && suffix == other.suffix
                );
            }
        };

        Alignment align(std::string strand1, std::string strand2);

        Aligner::Splitting split(std::string strand);

        std::vector<long> march(std::string strand1, std::string strand2);

        Meeting
        meet(std::vector<long>, std::vector<long>, std::string, char);

        template<typename T>
        T reversed(T copy);
    };
}


#endif //BLCKNX_EDITDISTANCEALIGNMENT_H
