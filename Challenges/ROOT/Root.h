//
// Created by Elmar Hinz on 2017-08-28 10:21:39.603359.
//

#ifndef BLCKNX_ROOT_H
#define BLCKNX_ROOT_H

#include <Challenge.h>

namespace blcknx {

    class Root : public Challenge {

    protected:
        unsigned model;
        unsigned result;

        void build() override;

        void calc() override;

        void format() override;

        unsigned int trees(unsigned int n);
    };

}


#endif //BLCKNX_<built-in method upper of str object at 0x105b7e260>_H