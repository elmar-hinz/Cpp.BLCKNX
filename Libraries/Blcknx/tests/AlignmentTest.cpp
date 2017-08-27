//
// Created by Elmar Hinz on 26.08.17.
//
#include "gtest/gtest.h"
#include "Alignment.h"

namespace blcknx {

    TEST(AlignmentTest, dummy) {
        EXPECT_EQ(1, 1);
    }

    TEST(AlignmentTest, gettersAndSetters) {
        Alignment alignment;
        alignment.setScore(-75);
        alignment.setStrand1("S1MS1");
        alignment.setStrand2("S2MMS2");
        alignment.setAlignment1("A-1");
        alignment.setAlignment2("A-2");
        alignment.setMotifBegin1(2);
        alignment.setMotifBegin2(2);
        alignment.setMotifLength1(1);
        alignment.setMotifLength2(2);
        EXPECT_EQ(-75, alignment.getScore());
        EXPECT_EQ("S1MS1", alignment.getStrand1());
        EXPECT_EQ("S2MMS2", alignment.getStrand2());
        EXPECT_EQ("A-1", alignment.getAlignment1());
        EXPECT_EQ("A-2", alignment.getAlignment2());
        EXPECT_EQ(2, alignment.getMotifBegin1());
        EXPECT_EQ(2, alignment.getMotifBegin2());
        EXPECT_EQ(1, alignment.getMotifLength1());
        EXPECT_EQ(2, alignment.getMotifLength2());
        EXPECT_EQ(3, alignment.getAlignmentLength());
        std::string expect = "Strand1: S1MS1\n"
                "Strand2: S2MMS2\n"
                "Score: -75\n"
                "Alignment length: 3\n"
                "Alignment1: A-1\n"
                "Alignment2: A-2\n"
                "Motif1 (2, 1): M\n"
                "Motif2 (2, 2): MM\n"
        ;
        EXPECT_EQ(expect, alignment.toString());
    }

    TEST(AlignmentTest, getMotifs) {
        Alignment alignment;
        alignment.setStrand1("ABBA");
        alignment.setStrand2("BCCB");
        alignment.setMotifBegin1(1);
        alignment.setMotifBegin2(1);
        alignment.setMotifLength1(2);
        alignment.setMotifLength2(2);
        EXPECT_EQ("BB", alignment.getMotif1());
        EXPECT_EQ("CC", alignment.getMotif2());
    }

}
