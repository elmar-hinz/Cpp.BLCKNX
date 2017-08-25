//
// Created by Elmar Hinz on 25.08.17.
//

#include <sstream>
#include <vector>
#include "TableReader.h"

namespace blcknx {

    void TableReader::read(
            std::string definition,
            std::map<char, std::map<char, int>> &table
    ) {

        std::stringstream rows(definition);
        std::vector<char> header;
        std::string row;

        // Read header
        char key;
        std::getline(rows, row, '\n');
        std::stringstream ss(row);
        ss >> key; // discard vertical index
        while (ss >> key) { header.push_back(key); }

        // Read lines
        std::string cell;
        int i = 0;
        while (std::getline(rows, row, '\n')) {
            std::stringstream ssr(row);
            std::getline(ssr, cell, ' '); // discard vertical index
            int j = 0;
            while (ssr >> cell) {
                table[header[i]][header[j]] = std::stoi(cell);
                j++;
            }
            i++;
        }
    }
}
