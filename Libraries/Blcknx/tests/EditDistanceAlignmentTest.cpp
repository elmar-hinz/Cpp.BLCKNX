//
// Created by Elmar Hinz on 22.08.17.
//


#include "gtest/gtest.h"

#define protected public
#include "EditDistanceAlignment.h"

TEST(EditDistanceAlignmentTest, setters_and_getters)
{
    blcknx::EditDistanceAlignment fixture;
    fixture.setStrand1("strand1");
    EXPECT_EQ("strand1", fixture.getStrand1());

    fixture.setStrand2("strand2");
    EXPECT_EQ("strand2", fixture.getStrand2());
}

TEST(EditDistanceAlignmentTest, full)
{
    blcknx::EditDistanceAlignment fixture;
    fixture.setStrand1("AABABABB");
    fixture.setStrand2("CACACAA");
    fixture.run();
    EXPECT_EQ("-A-ABABABB", fixture.getAlignment1());
    EXPECT_EQ("CACACA-A--", fixture.getAlignment2());
    EXPECT_EQ("AAAA", fixture.getLongestCommonSubsequence());
    EXPECT_EQ(6, fixture.getAlignmentDistance());
    EXPECT_EQ(4, fixture.getAlignmentScore());
    EXPECT_EQ(10, fixture.getAlignmentLength());
}
