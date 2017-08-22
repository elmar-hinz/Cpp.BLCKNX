//
// Created by Elmar Hinz on 20.08.17.
//

#include "gtest/gtest.h"
#include "Revc.h"

TEST(revc_test, reverse_complement)
{
    Revc challenge;
    std::string expect = "ACCGGGTTTT";
    EXPECT_EQ(expect, challenge.reverse_complement("AAAACCCGGT"));
}
