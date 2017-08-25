//
// Created by Elmar Hinz on 2017-08-23 14:17:46.413583.
//

#ifndef BLCKNX_GLOB_H
#define BLCKNX_GLOB_H

#include <Challenge.h>

namespace blcknx {

    class Glob : public Challenge {

    protected:
        std::pair<std::string, std::string> model;
        long result;

        void build() override;

        void calc() override;

        void format() override;

    };

}

#endif //BLCKNX_<built-in method upper of str object at 0x10aafabc8>_H