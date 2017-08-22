//
// Created by Elmar Hinz on 2017-08-22 13:05:12.113799.
//

#include "gtest/gtest.h"
#include "Edta.h"

TEST(edta_test, main)
{
    Edta challenge;
    std::string given = "> blcknx \n" "PRETTY\n" "> blcknx \n" "PRTTEIN";
    std::string expected = "4\n" "PRETT-Y-\n" "PR-TTEIN";
    EXPECT_EQ(expected, challenge.main(given));
}

