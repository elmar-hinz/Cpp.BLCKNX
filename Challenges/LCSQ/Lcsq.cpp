//
// Created by Elmar Hinz on 20.08.17.
//

#include "Lcsq.h"

void Lcsq::build() {
    model = fasta_strands(to_lines(input));
}

void Lcsq::calc() {
    result = longest_common_subsequence(model[0], model[1]);
}

void Lcsq::format() {
    output = result;
}

std::string Lcsq::longest_common_subsequence(
        std::string strand1,
        std::string strand2
) {
    Alignment alignment = align(std::move(strand1), std::move(strand2));
    std::string result;
    for (int i = 0; i < alignment.strand1.size(); ++i) {
        if (alignment.strand1[i] == alignment.strand2[i]) {
            result += alignment.strand1[i];
        }
    }
    return result;
}

Lcsq::Alignment Lcsq::align(std::string strand1, std::string strand2) {

    // Initialize
    if (strand1.empty()) {
        return {0, std::string(strand2.size(), '-'), strand2};
    }
    if (strand2.empty()) {
        return {0, strand1, std::string(strand1.size(), '-')};
    }

    // Split
    Splitting splitting = split(strand2);

    // Meet in the middle
    std::vector<unsigned> left = march(strand1, splitting.prefix);
    std::vector<unsigned> right
            = march(reversed(strand1), reversed(splitting.suffix));
    Meeting meeting = meet(left, reversed(right), strand1, splitting.splitter);

    // Divide and conquer
    Alignment left_alignment = align(meeting.prefix, splitting.prefix);
    Alignment right_alignment = align(meeting.suffix, splitting.suffix);

    // Build result
    Alignment alignment;
    alignment.score = meeting.score;
    alignment.strand1 = left_alignment.strand1
                        + meeting.char1
                        + right_alignment.strand1;
    alignment.strand2 = left_alignment.strand2
                        + meeting.char2
                        + right_alignment.strand2;
    return alignment;
}

Lcsq::Splitting Lcsq::split(std::string strand) {
    unsigned long middle = strand.size() / 2;
    Splitting splitting;
    splitting.prefix = strand.substr(0, middle);
    splitting.splitter = strand[middle];
    splitting.suffix = strand.substr(middle + 1, strand.size() - middle - 1);
    return splitting;
}

std::vector<unsigned> Lcsq::march(
        std::string strand1,
        std::string strand2
) {
    unsigned long height = strand1.size() + 1;
    unsigned long width = strand2.size() + 1;
    std::vector<unsigned> prev(height);
    std::vector<unsigned> curr(height);
    for (unsigned w = 1; w < width; w++) {
        curr[0] = 0;
        for (unsigned h = 1; h < height; h++) {
            unsigned alt[3] = {curr[h - 1], prev[h], prev[h - 1]};
            if (strand1[h - 1] == strand2[w - 1]) { alt[2] += 1; }
            curr[h] = *std::max_element(alt, alt + 3);
        }
        prev = curr;
    }
    return curr;
}

Lcsq::Meeting Lcsq::meet(
        std::vector<unsigned> left,
        std::vector<unsigned> right,
        std::string strand,
        char splitter
) {
    Meeting best = {0, '-', splitter, "", ""};
    unsigned long strandSize = strand.size();
    for (unsigned long l = 0; l <= strandSize; ++l) {
        std::string prefix, suffix;
        unsigned horizontal = left[l] + right[l];
        if (horizontal >= best.score) {
            prefix = strand.substr(0, l),
            suffix = strand.substr(l, strandSize - l);
            best = {horizontal, '-', splitter, prefix, suffix};
        }
        if (l > 0) {
            unsigned diagonal = left[l - 1] + right[l];
            char c = strand[l - 1];
            if (c == splitter) { diagonal += 1; }
            if (diagonal >= best.score) {
                prefix = strand.substr(0, l - 1);
                suffix = strand.substr(l, strandSize - l);
                best = {diagonal, c, splitter, prefix, suffix};
            }
        }
    }
    return best;
}

template<typename T>
T Lcsq::reversed(T copy) {
    std::reverse(copy.begin(), copy.end());
    return copy;
}


