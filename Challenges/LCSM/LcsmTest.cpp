#include "gtest/gtest.h"
#include "Lcsm.h"

TEST(lcsm_test, longest_common_shared_motif)
{
    Lcsm challenge;
    std::vector<std::string> given = {"GATTACA", "TAGACCA", "ATACA"};
    std::string expect = "TA";
    EXPECT_EQ(expect, challenge.longest_common_shared_motif(given));
}