//
// Created by Elmar Hinz on 2017-08-28 09:53:58.152499.
//

#include "Cunr.h"

namespace blcknx {

    void Cunr::build() {
        model = (unsigned) std::stoi(input);
    }

    void Cunr::format() {
        output = std::to_string(result);
    }

    void Cunr::calc() {
        result = count(model);
    }

    unsigned Cunr::count(unsigned n) {
        /*
        n : edges : trees
        -----------------
        2 : 1  : 1
        3 : 3  : 1
        4 : 5  : 3
        5 : 7  : 3 * 5   = 15
        6 : 9  : 7 * 15  = 105
        7 : 11 : 9 * 105 = 945
         */
        if (n == 2) { return 1; }
        return (2 * n - 5) * count(n - 1) % 1000000;
    }
}