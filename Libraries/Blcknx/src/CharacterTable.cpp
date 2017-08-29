//
// Created by Elmar Hinz on 28.08.17.
//

#include <vector>
#include <sstream>
#include <iostream>
#include "CharacterTable.h"

namespace blcknx {

    CharacterTable::CharacterTable(const std::string &newick) {
        read(newick);
    }

    void CharacterTable::read(std::string newick) {
        auto start = std::clock();
        tokens = tokenize(newick);
        {
            unsigned long characterCount = 0;
            std::vector<std::string> species;
            for (auto token: tokens) {
                if ((bool) std::isalpha(token[0])) { species.push_back(token); }
                if (token == "(") { characterCount++; }
            }
            std::sort(species.begin(), species.end());
            for (unsigned long i = 0; i < species.size(); ++i) {
                this->species[species[i]] = i;
            }
            table = std::vector<std::vector<bool>>(
                    characterCount,
                    std::vector<bool>(this->species.size()));
        }
        {
            unsigned long characterIndex = 0;
            std::vector<unsigned long> characterStack;
            for (auto token: tokens) {
                if (token == "(") {
                    characterStack.push_back(characterIndex);
                    characterIndex++;
                }
                // First character must be alpha (no underscore).
                if ((bool) std::isalpha(token[0])) {
                    unsigned long speciesIndex = species[token];
                    for (int i = 0; i < characterStack.size(); ++i) {
                        table[characterStack[i]][speciesIndex] = true;
                    }
                }
                if (token == ")") { characterStack.pop_back(); }
            }
        }
        table.erase(table.begin());
    }

    std::vector<std::string> CharacterTable::tokenize(std::string &newick) {
        std::vector<std::string> result;
        unsigned long current = 0, next = 0;
        while ((next = newick.find_first_of(";,()", current)) !=
               std::string::npos) {
            if (next - current > 0) {
                result.push_back(newick.substr(current, next - current));
            }
            result.push_back(newick.substr(next, 1));
            current = next + 1;
        }
        return result;
    }

    std::string CharacterTable::to_string(CharacterTable table) {
        std::stringstream out;
        for (auto row : table.table) {
            for (auto cell : row) { out << std::to_string((int) cell); }
            out << std::endl;
        }
        return out.str();
    }

    std::vector<std::string> CharacterTable::getSpecies() const {
        std::vector<std::string> result;
        for (auto &&mapping : species) {
            result.push_back(mapping.first);
        }
        return result;
    }

    std::vector<std::vector<bool>> CharacterTable::getTable() const {
        return table;
    }

    std::vector<std::string> CharacterTable::getCharacterIds() const {
        std::vector<std::string > result;
        for (const auto &row : table) {
            std::string id;
            for (auto &&entry : row) { id += entry ? "1" : "0"; }
            result.push_back(id);
        }
        return result;
    }


    unsigned long CharacterTable::getAmountOfSpecies() const {
        return getSpecies().size();
    }

}
