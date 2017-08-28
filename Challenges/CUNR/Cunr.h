//
// Created by Elmar Hinz on 2017-08-28 09:53:58.152183.
//

#ifndef BLCKNX_CUNR_H
#define BLCKNX_CUNR_H

#include <Challenge.h>

namespace blcknx {

    class Cunr : public Challenge {

    protected:
        unsigned model;
        unsigned result;

        void build() override;

        void calc() override;

        void format() override;

        unsigned count(unsigned n);
    };

}


#endif //BLCKNX_<built-in method upper of str object at 0x10a0c1308>_H