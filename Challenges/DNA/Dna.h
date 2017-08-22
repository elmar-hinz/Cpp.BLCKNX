//
// Created by Elmar Hinz on 20.08.17.
//

#ifndef BLCKNX_DNA_H
#define BLCKNX_DNA_H

#include <Challenge.h>

class Dna : public challenges::Challenge {

public:
    void build() override;

    void calc() override;

    void format() override;

    std::vector<unsigned > count_nucleotides(std::string);

protected:
    std::string model;
    std::vector<unsigned > result;
};


#endif //BLCKNX_DNA_H
