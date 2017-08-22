//
// Created by Elmar Hinz on 20.08.17.
//

#ifndef BLCKNX_SUBS_H
#define BLCKNX_SUBS_H

#include <map>
#include <Challenge.h>

class Subs : public blcknx::Challenge {

public:

    void build() override;

    void calc() override;

    void format() override;

    std::vector<unsigned> positions(std::string strand, std::string motif);

protected:
    std::map<std::string, std::string> model;
    std::vector<unsigned> result;
};


#endif //BLCKNX_SUBS_H
