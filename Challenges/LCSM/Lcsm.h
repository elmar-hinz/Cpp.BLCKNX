//
// Created by Elmar Hinz on 20.08.17.
//

#ifndef BLCKNX_LCSM_H
#define BLCKNX_LCSM_H

#include <Challenge.h>

class Lcsm : public challenges::Challenge {

    public:
        void build() override;

        void calc() override;

        void format() override;

        std::string longest_common_shared_motif(std::vector<std::string> strands);

    protected:
        std::vector<std::string > model;
        std::string result;
};


#endif //BLCKNX_LCSM_H
