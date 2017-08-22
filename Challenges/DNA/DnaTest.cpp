//
// Created by Elmar Hinz on 20.08.17.
//

#include "gtest/gtest.h"
#include "Dna.h"

TEST(dna_test, count_nucleotides)
{
    Dna challenge;
    std::vector<unsigned > expect{1, 2, 3, 4};
    EXPECT_EQ(expect, challenge.count_nucleotides("ACCGGGTTTT"));
}
