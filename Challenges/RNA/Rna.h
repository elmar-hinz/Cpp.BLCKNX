//
// Created by Elmar Hinz on 20.08.17.
//

#ifndef BLCKNX_RNA_H
#define BLCKNX_RNA_H

#include <Challenge.h>

class Rna : public blcknx::Challenge {

public:
    void build() override;

    void calc() override;

    void format() override;

    std::string transcribe_dna_to_rna(std::string);

protected:
    std::string model;
    std::string result;
};



#endif //BLCKNX_RNA_H
