//
// Created by Elmar Hinz on 28.08.17.
//

#ifndef BLCKNX_CHARACTERTABLE_H
#define BLCKNX_CHARACTERTABLE_H


#include <string>
#include <map>
#include <vector>

namespace blcknx {
    class CharacterTable {
    public:
        explicit CharacterTable(const std::string &newick);

        static std::string to_string(CharacterTable characterTable);

        std::vector<std::string> getSpecies() const;

        unsigned long getAmountOfSpecies() const;

        std::vector<std::vector<bool>> getTable() const;

        std::vector<std::string> getCharacterIds() const;

    protected:
        std::vector<std::string> tokens;
        std::map<std::string, unsigned long> species;
        std::vector<std::vector<bool>> table;

        std::vector<std::string> tokenize(std::string &newick);

        void read(std::string newick);

    };

}

#endif //BLCKNX_CHARACTERTABLE_H
