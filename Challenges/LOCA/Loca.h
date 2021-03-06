//
// Created by Elmar Hinz on 2017-08-24 20:30:21.370382.
//

#ifndef BLCKNX_LOCA_H
#define BLCKNX_LOCA_H

#include <Challenge.h>
#include "Aligner.h"
#include "Pam250ScoreProvider.h"

namespace blcknx {

    class Loca : public Challenge {

    protected:
        void build() override;

        void calc() override;

        void format() override;

        std::vector<std::string> model;
        Pam250ScoreProvider provider;
        Aligner aligner;
        Alignment result;
    };

}


#endif //BLCKNX_<built-in method upper of str object at 0x1072be768>_H