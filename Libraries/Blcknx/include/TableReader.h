//
// Created by Elmar Hinz on 25.08.17.
//

#ifndef BLCKNX_TABLEREADER_H
#define BLCKNX_TABLEREADER_H

#include <string>
#include <map>

namespace blcknx {
    class TableReader {
    public:
        static void read(
                std::string definition,
                std::map<char, std::map<char, int>> &table
        );
    };
}

#endif //BLCKNX_TABLEREADER_H
