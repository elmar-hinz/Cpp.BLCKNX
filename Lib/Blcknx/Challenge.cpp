//
// Created by Elmar Hinz on 19.08.17.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Challenge.h"

namespace challenges {

    void Challenge::run() {
        Challenge challenge;
        std::string input, line;
        while (std::getline(std::cin, line)) {
            input += line + "\n";
        }
        std::cout << challenge.main(input);
    }

    std::string Challenge::main(std::string input) {
        this->input = std::move(input);
        build();
        calc();
        format();
        return output;
    }

    std::vector<std::string> Challenge::fasta_strands(std::vector<std::string> lines)
    {
        std::vector<std::string> strands;
        std::string strand;
        for (auto &line : lines) {
            if(line[0] == '>') {
                if(!strand.empty()) {
                    strands.push_back(strand);
                    strand = "";
                }
            } else {
                strand += line;
            }
        }
        strands.push_back(strand);
        return strands;
    }

    std::vector<std::string> Challenge::to_lines(std::string input)
    {
        std::stringstream ss(input);
        std::string item;
        std::vector<std::string> result;
        while(std::getline(ss, item)) {
            result.push_back(item);
        }
        return result;
    }

}


