//
// Created by Elmar Hinz on 26.08.17.
//

#ifndef BLCKNX_ALIGNMENT_H
#define BLCKNX_ALIGNMENT_H

namespace blcknx {
    class Alignment {
    public:
        const std::string &getStrand1() const;

        void setStrand1(const std::string &strand1);

        const std::string &getStrand2() const;

        void setStrand2(const std::string &strand2);

        const std::string &getAlignment1() const;

        void setAlignment1(const std::string &alignment1);

        const std::string &getAlignment2() const;

        void setAlignment2(const std::string &alignment2);

        unsigned long getMotifBegin1() const;

        void setMotifBegin1(unsigned long motifBegin1);

        unsigned long getMotifBegin2() const;

        void setMotifBegin2(unsigned long motifBegin2);

        unsigned long getMotifLength1() const;

        void setMotifLength1(unsigned long motifLength1);

        unsigned long getMotifLength2() const;

        void setMotifLength2(unsigned long motifLength2);

        const std::string getMotif1() const;

        const std::string getMotif2() const;

        unsigned long getAlignmentLength();

    protected:
        long score;
    public:
        long getScore() const;

        void setScore(long score);

    protected:
        std::string strand1;
        std::string strand2;
        std::string alignment1;
        std::string alignment2;
        unsigned long motifBegin1;
        unsigned long motifBegin2;
        unsigned long motifLength1;
        unsigned long motifLength2;
    };
}
#endif //BLCKNX_ALIGNMENT_H
