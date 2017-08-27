//
// Created by Elmar Hinz on 22.08.17.
//

#ifndef BLCKNX_EDITDISTANCEALIGNMENT_H
#define BLCKNX_EDITDISTANCEALIGNMENT_H

#include <string>
#include "Alignment.h"

namespace blcknx {
    class AlignmentScoreProviderInterface;

    class AlignmentScoreProviderInterface;

    class Aligner {
    public:

        void setScoreProvider(AlignmentScoreProviderInterface *scoreProvider);

        void setStrand1(const std::string &strand1);

        void setMotifOrStrand2(const std::string &strand2);

        const Alignment getAlignment() const;

        void alignGlobally();

        void alignLocally();

        void alignFitting();

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
            long score;
            char char1;
            char char2;
            std::string prefix;
            std::string suffix;

            bool operator==(const Meeting &other) const {
                return (score == other.score
                        && char1 == other.char1
                        && char2 == other.char2
                        && prefix == other.prefix
                        && suffix == other.suffix
                );
            }
        };

        Alignment align(
                const std::string &strand1,
                const std::string &strand2,
                bool freeRidesLeft = false,
                bool freeRidesRight = false
        );

        Aligner::Splitting split(std::string strand);

        std::vector<long> march(
                const std::string & strand1,
                const std::string & strand2,
                bool zeroBorders = false
        );

        Meeting
        meet(std::vector<long>, std::vector<long>, std::string, char);

        template<typename T>
        T reversed(T copy);

        long worstScore();
    };
}


#endif //BLCKNX_EDITDISTANCEALIGNMENT_H
