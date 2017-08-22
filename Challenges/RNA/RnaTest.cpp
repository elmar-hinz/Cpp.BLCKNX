//
// Created by Elmar Hinz on 20.08.17.
//
#include "gtest/gtest.h"
#include "Rna.h"

TEST(rna_test, transcribe_dna_to_rna)
{
    Rna challenge; 
    std::string expect = "ACGUU";
    EXPECT_EQ(expect, challenge.transcribe_dna_to_rna("ACGTU"));
}

