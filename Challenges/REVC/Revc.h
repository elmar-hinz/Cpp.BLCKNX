//
// Created by Elmar Hinz on 20.08.17.
//

#ifndef BLCKNX_REVC_H
#define BLCKNX_REVC_H

#include <Challenge.h>

class Revc : public challenges::Challenge {

public:
    void build() override;

    void calc() override;

    void format() override;

    std::string reverse_complement(std::string strand);

protected:
    std::string model;
    std::string result;

};


#endif //BLCKNX_REVC_H
