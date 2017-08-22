//
// Created by Elmar Hinz on 20.08.17.
//

#include "gtest/gtest.h"
#include "Subs.h"

TEST(subs_test, positions)
{
    Subs challenge;
    std::vector<unsigned > expect{2, 4, 10};
    std::string strand = "GATATATGCATATACTT";
    std::string motif = "ATAT";
    EXPECT_EQ(expect, challenge.positions(strand, motif));
}