//
// Created by Elmar Hinz on 20.08.17.
//

#ifndef BLCKNX_LCSQ_H
#define BLCKNX_LCSQ_H

#include <Challenge.h>

class Lcsq : public challenges::Challenge {

public:
    void build() override;

    void calc() override;

    void format() override;

private:
    std::vector<std::string> model;
    std::string result;

    struct Alignment {
        unsigned score;
        std::string strand1;
        std::string strand2;

        bool operator==(const Alignment &other) const {
            return (score == other.score
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
        unsigned score;
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

    std::string longest_common_subsequence(std::string strand1, std::string strand2);

    Alignment align(std::string strand1, std::string strand2);

    Splitting split(std::string strand);

    std::vector<unsigned int> march(std::string strand1, std::string strand2);

    Meeting meet(std::vector<unsigned>, std::vector<unsigned>, std::string, char);

    template<typename T>
    T reversed(T copy);

};


#endif //BLCKNX_LCSQ_H
