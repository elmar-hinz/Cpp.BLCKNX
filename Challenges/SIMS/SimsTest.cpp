//
// Created by Elmar Hinz on 2017-08-27 07:50:16.428359.
//

#include "gtest/gtest.h"

#define protected public
#define private public

#include "Sims.h"

namespace blcknx {

    TEST(sims_test, main) {
        Sims challenge;
        std::string given = "> BLCKNX \n"
                "GCAAACCATAAGCCCTACGTGCCGCCTGTTTAAACTCGCGAACTGAATCTTCTGCTTCACGGTGAAAGTACCACAATGGTATCACACCCCAAGGAAAC\n"
                "> BLCKNX \n"
                "GCCGTCAGGCTGGTGTCCG";
        std::string expected = "5\n"
                "-CCATAAGCCCTACGTG-CCG\n"
                "GCCGTCAGGC-TG-GTGTCCG";
        EXPECT_EQ(expected, challenge.main(given));
    }

    TEST(sims_test, build) {
        Sims challenge;
        challenge.input = "> BLCKNX \n"
                "GCAAACCATAAGCCCTACGTGCCGCCTGTTTAAACTCGCGAACTGAATCTTCTGCTTCACGGTGAAAGTACCACAATGGTATCACACCCCAAGGAAAC\n"
                "> BLCKNX \n"
                "GCCGTCAGGCTGGTGTCCG";
        std::vector<std::string> expected = {
                "GCAAACCATAAGCCCTACGTGCCGCCTGTTTAAACTCGCGAACTGAATCTTCTGCTTCACGGTGAAAGTACCACAATGGTATCACACCCCAAGGAAAC",
                "GCCGTCAGGCTGGTGTCCG"
        };
        challenge.build();
        EXPECT_EQ(expected, challenge.model);
    }

    TEST(sims_test, format) {
        Sims challenge;
        challenge.result.setScore(5);
        challenge.result.setAlignment1("ACCATAAGCCCTACGTG-CCG");
        challenge.result.setAlignment2("GCCGTCAGGC-TG-GTGTCCG");
        std::string expected = "5\nACCATAAGCCCTACGTG-CCG\nGCCGTCAGGC-TG-GTGTCCG";
        challenge.format();
        EXPECT_EQ(expected, challenge.output);
    }

}