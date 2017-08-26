//
// Created by Elmar Hinz on 2017-08-22 13:05:12.113157.
//

#ifndef BLCKNX_EDTA_H
#define BLCKNX_EDTA_H

#include <Challenge.h>
#include "Aligner.h"
#include "EditDistanceScoreProvider.h"

namespace blcknx {

    class Edta : public blcknx::Challenge {

    protected:
        void build() override;

        void calc() override;

        void format() override;

        std::vector<std::string> model;
        blcknx::Alignment result;
        blcknx::EditDistanceScoreProvider provider;
    };

}
#endif //BLCKNX