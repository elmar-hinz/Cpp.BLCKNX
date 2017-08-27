//
// Created by Elmar Hinz on 2017-08-27 07:50:16.427754.
//

#ifndef BLCKNX_SIMS_H
#define BLCKNX_SIMS_H

#include <Challenge.h>
#include "MismatchScoreProvider.h"
#include "Aligner.h"

namespace blcknx {

    class Sims : public Challenge {

    protected:
        void build() override;

        void calc() override;

        void format() override;

        std::vector<std::string> model;
        MismatchScoreProvider provider;
        Aligner aligner;
        Alignment result;
    };

}


#endif //BLCKNX_<built-in method upper of str object at 0x1048d28f0>_H