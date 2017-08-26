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
        alignment.setStrand1("S1");
        alignment.setStrand2("S2");
        alignment.setAlignment1("A1");
        alignment.setAlignment2("A2");
        alignment.setMotifBegin1(11);
        alignment.setMotifBegin2(22);
        EXPECT_EQ(-75, alignment.getScore());
        EXPECT_EQ("S1", alignment.getStrand1());
        EXPECT_EQ("S2", alignment.getStrand2());
        EXPECT_EQ("A1", alignment.getAlignment1());
        EXPECT_EQ("A2", alignment.getAlignment2());
        EXPECT_EQ(11, alignment.getMotifBegin1());
        EXPECT_EQ(22, alignment.getMotifBegin2());
        EXPECT_EQ(2, alignment.getAlignmentLength());
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
