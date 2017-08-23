//
// Created by Elmar Hinz on 23.08.17.
//

#include "EditDistance.h"
#include <numeric>

namespace blcknx {

    unsigned long EditDistance::measure(std::string strand1, std::string strand2) {
        std::vector<unsigned long> current, last(strand1.size() + 1);
        std::iota(last.begin(), last.end(), 0);
        for (unsigned long w = 0; w < strand2.size(); ++w) {
            current = {w + 1};
            for (unsigned long h = 0; h < strand1.size(); ++h) {
                unsigned long indel
                        = std::min(current[h], last[h + 1]) + 1;
                unsigned long match = last[h] +
                                      static_cast<unsigned long>( strand1[h] !=
                                                                  strand2[w]);
                current.push_back(std::min(indel, match));
            }
            last = current;
        }
        return last.back();
    }
}
