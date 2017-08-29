//
// Created by Elmar Hinz on 2017-08-29 11:10:13.427248.
//

#ifndef BLCKNX_SPTD_H
#define BLCKNX_SPTD_H

#include <Challenge.h>

namespace blcknx {

    class Sptd : public Challenge {

    protected:
        std::pair<std::string, std::string > model;
        unsigned long result;
        void build() override;

        void calc() override;

        void format() override;

    };

}


#endif //BLCKNX_<built-in method upper of str object at 0x10c798260>_H