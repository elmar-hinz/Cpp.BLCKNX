//
// Created by Elmar Hinz on 19.08.17.
//

#ifndef BLCKNX_CHALLENGE_H
#define BLCKNX_CHALLENGE_H

#include <iostream>
#include <vector>

namespace blcknx {

    class Challenge {

    public:
        void run();

        std::string main(std::string input);

        const std::string &getInput() const;

        void setInput(const std::string &input);

        const std::string &getOutput() const;

        void setOutput(const std::string &output);

    protected:
        std::clock_t startTimeClock;
        std::string input;
        std::string output;

        virtual void build() {};

        virtual void calc() {};

        virtual void format() {};

        std::vector<std::string> to_lines(std::string input);

        std::vector<std::string> fasta_strands(std::vector<std::string> lines);

        void logDuration(std::string msg="");

    };

}

#endif //BLCKNX_CHALLENGE_H
