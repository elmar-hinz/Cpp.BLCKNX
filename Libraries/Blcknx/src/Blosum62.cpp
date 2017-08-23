//
// Created by Elmar Hinz on 23.08.17.
//

#include <sstream>
#include <vector>
#include "Blosum62.h"

int blcknx::Blosum62::get(char char1, char char2) {
    return table[char1][char2];
}

blcknx::Blosum62::Blosum62() {
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
    int j = 0;
    while (std::getline(rows, row, '\n')) {
        std::stringstream ssr(row);
        std::getline(ssr, cell, ' '); // discard vertical index
        while (ssr >> cell) {
            table[header[i]][header[j]] = std::stoi(cell);
            table[header[j]][header[i]] = std::stoi(cell);
            j++;
        }
        i++;
    }
}
