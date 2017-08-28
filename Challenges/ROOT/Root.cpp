//
// Created by Elmar Hinz on 2017-08-28 10:21:39.603684.
//

#include "Root.h"

namespace blcknx {

    void Root::build() {
        model = (unsigned) std::stoi(input);
    }

    void Root::format() {
        output = std::to_string(result);
    }

    void Root::calc() {
        result = trees(model);
    }

    unsigned Root::trees(unsigned n) {
        if (n == 2) { return 1; }
        return trees(n - 1)         // previous trees
               * ((n - 1) * 2 - 1)  // previous edges
               % 1000000;
    }

}