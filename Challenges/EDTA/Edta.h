//
// Created by Elmar Hinz on 2017-08-22 13:05:12.113157.
//

#ifndef BLCKNX_EDTA_H
#define BLCKNX_EDTA_H

#include <Challenge.h>
#include "EditDistanceAlignment.h"

class Edta : public blcknx::Challenge {

public:
    void build() override;

    void calc() override;

    void format() override;

protected:
    std::vector<std::string> model;
    blcknx::EditDistanceAlignment result;
};


#endif //BLCKNX