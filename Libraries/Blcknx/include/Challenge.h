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
        std::string main(std::string input);

        static void run();

    protected:

        std::string input;
        std::string output;

        virtual void build() {};

        virtual void calc() {};

        virtual void format() {};

        std::vector<std::string> to_lines(std::string input);

        std::vector<std::string> fasta_strands(std::vector<std::string> lines);

    };

}

#endif //BLCKNX_CHALLENGE_H
