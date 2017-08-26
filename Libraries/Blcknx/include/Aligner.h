//
// Created by Elmar Hinz on 22.08.17.
//

#ifndef BLCKNX_EDITDISTANCEALIGNMENT_H
#define BLCKNX_EDITDISTANCEALIGNMENT_H

#include <string>
#include "EditDistanceScoreProvider.h"
#include "Alignment.h"

namespace blcknx {
    class AlignmentScoreProviderInterface;

    class AlignmentScoreProviderInterface;

    class Aligner {
    public:

        void setScoreProvider(AlignmentScoreProviderInterface *scoreProvider);

        void setStrand1(const std::string &strand1);

        void setStrand2(const std::string &strand2);

        const Alignment getAlignment() const;

        void run();

    protected:
        Alignment alignment;
        AlignmentScoreProviderInterface *scoreProvider;

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

        long worstScore();
    };
}


#endif //BLCKNX_EDITDISTANCEALIGNMENT_H
