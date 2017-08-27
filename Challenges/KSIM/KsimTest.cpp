//
// Created by Elmar Hinz on 2017-08-27 15:34:59.888631.
//

#include "gtest/gtest.h"

#define protected public
#define private public

#include "Ksim.h"

namespace blcknx {

    TEST(ksim_test, build) {
        Ksim challenge;
        challenge.input = "2\n" "ACGTAG\n" "ACGGATCGGCATCGT";
        challenge.build();
        Ksim::Model expected = {2, "ACGTAG", "ACGGATCGGCATCGT"};
        EXPECT_EQ(expected, challenge.model);
    }

    TEST(ksim_test, format) {
        Ksim challenge;
        challenge.result = {{1, 2}, {3, 4}};
        challenge.format();
        std::string expectation = "1 2\n3 4";
        EXPECT_EQ(expectation, challenge.output);
    }

    TEST(ksim_test, main1) {
        Ksim challenge;
        std::string given = "2\n"
                "ACGTAG\n"
                "ACGGATCGGCATCGT";
        std::string expected = "1 4\n"
                "1 5\n"
                "1 6";
        EXPECT_EQ(expected, challenge.main(given));
    }

    TEST(ksim_test, main2) {
        Ksim challenge;
        std::string given = "1\n"
                "ACGTAG\n"
                "GGACGATAGGTAAAGTAGTAGCGACGTAGG";

        std::string expected = "3 7\n"
                "13 6\n"
                "14 5\n"
                "17 5\n"
                "23 7\n"
                "24 5\n"
                "24 6\n"
                "24 7\n"
                "25 5";
        EXPECT_EQ(expected, challenge.main(given));
    }
}