//
// Created by Elmar Hinz on 23.08.17.
//
#include "gtest/gtest.h"
#include "Blosum62.h"

namespace {

    TEST(Blosum62Test, full)
    {
        blcknx::Blosum62 blosum62;
        EXPECT_EQ(4, blosum62.get('A', 'A'));
        EXPECT_EQ(-2, blosum62.get('A', 'Y'));
        EXPECT_EQ(-2, blosum62.get('Y', 'A'));
    }

}

