//
// Created by Elmar Hinz on 22.08.17.
//

#include <vector>
#include <numeric>
#include "EditDistanceAlignment.h"

namespace blcknx {

    const std::string &EditDistanceAlignment::getStrand1() const {
        return strand1;
    }

    void EditDistanceAlignment::setStrand1(const std::string &strand1) {
        EditDistanceAlignment::strand1 = strand1;
    }

    const std::string &EditDistanceAlignment::getStrand2() const {
        return strand2;
    }

    void EditDistanceAlignment::setStrand2(const std::string &strand2) {
        EditDistanceAlignment::strand2 = strand2;
    }

    void EditDistanceAlignment::run() {
        Alignment alignment = align(strand1, strand2);
        alignment1 = alignment.strand1;
        alignment2 = alignment.strand2;
        alignmentLength = alignment1.size();
        alignmentDistance = alignment.distance;
    }

    const std::string &EditDistanceAlignment::getAlignment1() const {
        return alignment1;
    }

    const std::string &EditDistanceAlignment::getAlignment2() const {
        return alignment2;
    }

    unsigned long EditDistanceAlignment::getAlignmentDistance() const {
        return alignmentDistance;
    }

    unsigned long EditDistanceAlignment::getAlignmentLength() const {
        return alignmentLength;
    }

    EditDistanceAlignment::Alignment EditDistanceAlignment::align(
            std::string strand1, std::string strand2
    ) {

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
        std::vector<unsigned long> left = march(strand1, splitting.prefix);
        std::vector<unsigned long> right = march(reversed(strand1),
                                                 reversed(splitting.suffix));
        Meeting meeting = meet(left, reversed(right), strand1,
                               splitting.splitter);

        // Divide and conquer
        Alignment left_alignment = align(meeting.prefix, splitting.prefix);
        Alignment right_alignment = align(meeting.suffix, splitting.suffix);

        // Build result
        Alignment alignment;
        alignment.distance = meeting.distance;
        alignment.strand1 = left_alignment.strand1
                            + meeting.char1
                            + right_alignment.strand1;
        alignment.strand2 = left_alignment.strand2
                            + meeting.char2
                            + right_alignment.strand2;
        return alignment;
    }

    std::vector<unsigned long> EditDistanceAlignment::march(
            std::string strand1,
            std::string strand2
    ) {
        std::vector<unsigned long> current, last(strand1.size() + 1);
        std::iota(last.begin(), last.end(), 0);
        for (unsigned long w = 0; w < strand2.size(); ++w) {
            current = {w + 1};
            for (unsigned long h = 0; h < strand1.size(); ++h) {
                unsigned long indel
                        = std::min(current[h], last[h + 1]) + 1;
                unsigned long match = last[h] +
                                      static_cast<unsigned long>( strand1[h] !=
                                                                  strand2[w]);
                current.push_back(std::min(indel, match));
            }
            last = current;
        }
        return last;
    }

    EditDistanceAlignment::Meeting EditDistanceAlignment::meet(
            std::vector<unsigned long> left,
            std::vector<unsigned long> right,
            std::string strand,
            char splitter
    ) {
        unsigned long max = strand1.size() + strand2.size();
        Meeting best = {max , '-', splitter, "", ""};
        unsigned long strandSize = strand.size();
        for (unsigned long l = 0; l <= strandSize; ++l) {
            std::string prefix, suffix;
            unsigned long horizontal = left[l] + right[l] + 1;
            if (horizontal < best.distance) {
                prefix = strand.substr(0, l);
                suffix = strand.substr(l, strandSize - l);
                best = {horizontal, '-', splitter, prefix, suffix};
            }
            if (l > 0) {
                unsigned long diagonal = left[l - 1] + right[l];
                char c = strand[l - 1];
                if (c != splitter) { diagonal += 1; }
                if (diagonal < best.distance) {
                    prefix = strand.substr(0, l - 1);
                    suffix = strand.substr(l, strandSize - l);
                    best = {diagonal, c, splitter, prefix, suffix};
                }
            }
        }
        return best;
    }

    EditDistanceAlignment::Splitting
    EditDistanceAlignment::split(std::string strand) {
        unsigned long middle = strand.size() / 2;
        Splitting splitting;
        splitting.prefix = strand.substr(0, middle);
        splitting.splitter = strand[middle];
        splitting.suffix = strand.substr(middle + 1,
                                         strand.size() - middle - 1);
        return splitting;
    }

    template<typename T>
    T EditDistanceAlignment::reversed(T copy) {
        std::reverse(copy.begin(), copy.end());
        return copy;
    }

}
