//
// Created by Elmar Hinz on 2017-08-22 13:05:12.113799.
//

#include "gtest/gtest.h"
#include "Edta.h"

TEST(edta_test, main)
{
    /**
     * 4
     * PRETTY--
     * PR-TTEIN
     *
     * 4
     * PRETT-Y
     * PRTTEIN
     */
    Edta challenge;
    std::string given = "> blcknx \n" "PRETTY\n" "> blcknx \n" "PRTTEIN";
    std::string expected = "4\n" "PRETT-Y\n" "PRTTEIN";
    EXPECT_EQ(expected, challenge.main(given));
}

