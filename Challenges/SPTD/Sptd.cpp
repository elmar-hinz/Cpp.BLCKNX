//
// Created by Elmar Hinz on 2017-08-29 11:10:13.427657.
//

#include <algorithm>
#include <vector>
#include "Sptd.h"
#include "CharacterTable.h"

namespace blcknx {

    void Sptd::build() {
        std::vector<std::string> lines = to_lines(input);
        model.first = lines[1];
        model.second = lines[2];
    }

    void Sptd::calc() {
        CharacterTable table1(model.first);
        CharacterTable table2(model.second);
        std::vector<std::string > ids1 = table1.getCharacterIds();
        std::vector<std::string > ids2 = table2.getCharacterIds();
        std::sort(ids1.begin(), ids1.end());
        std::sort(ids2.begin(), ids2.end());

        {
            std::vector<std::string > difference(ids1.size());
            auto it = std::set_difference(ids1.begin(), ids1.end(),
                                          ids2.begin(), ids2.end(),
                                          difference.begin());
            difference.resize((unsigned long) (it - difference.begin()));
            result = difference.size();
        }
        {
            std::vector<std::string > difference(ids2.size());
            auto it = std::set_difference(ids2.begin(), ids2.end(),
                                          ids1.begin(), ids1.end(),
                                          difference.begin());
            difference.resize((unsigned long) (it - difference.begin()));
            result += difference.size();
        }
    }

    void Sptd::format() {
        output = std::to_string(result);
    }

}