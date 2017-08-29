//
// Created by Elmar Hinz on 19.08.17.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Challenge.h"

namespace blcknx {

    void Challenge::run() {
        std::string input, line;
        while (std::getline(std::cin, line)) {
            input += line + "\n";
        }
        std::cout << main(input) << std::endl;
    }

    std::string Challenge::main(std::string input) {
        startTimeClock = std::clock();
        this->input = std::move(input);
        build();
        calc();
        format();
        return output;
    }

    std::vector<std::string>
    Challenge::fasta_strands(std::vector<std::string> lines) {
        std::vector<std::string> strands;
        std::string strand;
        for (auto &line : lines) {
            if (line[0] == '>') {
                if (!strand.empty()) {
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

    std::vector<std::string> Challenge::to_lines(std::string input) {
        std::stringstream ss(input);
        std::string item;
        std::vector<std::string> result;
        while (std::getline(ss, item)) {
            result.push_back(item);
        }
        return result;
    }

    const std::string &Challenge::getInput() const {
        return input;
    }

    void Challenge::setInput(const std::string &input) {
        this->input = input;
    }

    const std::string &Challenge::getOutput() const {
        return output;
    }

    void Challenge::setOutput(const std::string &output) {
        this->output = output;
    }

    void Challenge::logDuration(std::string msg) {
        std::clock_t endClock = std::clock();
        std::cerr << "* " << (endClock - startTimeClock) << " ms - " << msg
                  << "\n";

    }

}


