//
// Created by Elmar Hinz on 26.08.17.
//

#include <string>
#include "Alignment.h"

namespace blcknx {

    long Alignment::getScore() const {
        return score;
    }

    void Alignment::setScore(long score) {
        Alignment::score = score;
    }

    const std::string &Alignment::getStrand1() const {
        return strand1;
    }

    void Alignment::setStrand1(const std::string &strand1) {
        this->strand1 = strand1;
    }

    const std::string &Alignment::getStrand2() const {
        return strand2;
    }

    void Alignment::setStrand2(const std::string &strand2) {
        this->strand2 = strand2;
    }

    const std::string &Alignment::getAlignment1() const {
        return alignment1;
    }

    void Alignment::setAlignment1(const std::string &alignment1) {
        this->alignment1 = alignment1;
    }

    const std::string &Alignment::getAlignment2() const {
        return alignment2;
    }

    void Alignment::setAlignment2(const std::string &alignment2) {
        this->alignment2 = alignment2;
    }

    unsigned long Alignment::getMotifBegin1() const {
        return motifBegin1;
    }

    void Alignment::setMotifBegin1(unsigned long motifBegin1) {
        this->motifBegin1 = motifBegin1;
    }

    unsigned long Alignment::getMotifBegin2() const {
        return motifBegin2;
    }

    void Alignment::setMotifBegin2(unsigned long motifBegin2) {
        this->motifBegin2 = motifBegin2;
    }

    unsigned long Alignment::getMotifLength1() const {
        return motifLength1;
    }

    void Alignment::setMotifLength1(unsigned long motifLength1) {
        this->motifLength1 = motifLength1;

    }

    unsigned long Alignment::getMotifLength2() const {
        return motifLength2;
    }

    void Alignment::setMotifLength2(unsigned long motifLength2) {
        this->motifLength2 = motifLength2;
    }

    const std::string  Alignment::getMotif1() const {
        return strand1.substr(motifBegin1, motifLength1);
    }

    const std::string  Alignment::getMotif2() const {
        return strand2.substr(motifBegin2, motifLength2);
    }

    unsigned long Alignment::getAlignmentLength() const {
        return alignment1.size();
    }

}

