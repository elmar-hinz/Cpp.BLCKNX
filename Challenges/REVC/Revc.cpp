//
// Created by Elmar Hinz on 20.08.17.
//

#include <map>
#include "Revc.h"

void Revc::build() {
    model = to_lines(input)[0];
}

void Revc::calc() {
    result = reverse_complement(model);
}

void Revc::format() {
        output = result;
}

char complement(char c)
{
    char ret;
    if (c == 'A') {
        ret = 'T';
    } else if (c == 'C') {
        ret = 'G';
    } else if (c == 'G') {
        ret = 'C';
    } else if (c == 'T') {
        ret = 'A';
    } else {
        ret = 'X';
    }
    return ret;
}

std::string Revc::reverse_complement(std::string strand)
{
    std::string result;
    reverse(strand.begin(), strand.end());
    for (char i : strand) {
        result += complement(i);
    }
    return result;
}
