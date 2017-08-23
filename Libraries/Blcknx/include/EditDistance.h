//
// Created by Elmar Hinz on 23.08.17.
//

#ifndef BLCKNX_EDITDISTANCE_H
#define BLCKNX_EDITDISTANCE_H

#include <vector>
#include <string>

namespace blcknx {
    class EditDistance {
    public:
        static unsigned long measure(std::string strand1, std::string strand2);
    };
}

#endif //BLCKNX_EDITDISTANCE_H
