//
// Created by Elmar Hinz on 21.08.17.
//

#ifndef BLCKNX_EDIT_H
#define BLCKNX_EDIT_H

#include "Challenge.h"

class Edit : public challenges::Challenge {

protected:
    std::pair<std::string, std::string> model;
    unsigned result;

    void build() override;

    void calc() override;

    void format() override;

    unsigned edit_distance(std::string strand1, std::string strand2);
};


#endif //BLCKNX_EDIT_H
