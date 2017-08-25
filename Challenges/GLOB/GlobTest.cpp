//
// Created by Elmar Hinz on 2017-08-23 14:17:46.414713.
//

#include "gtest/gtest.h"

#define protected public
#define private public

#include "Glob.h"

namespace blcknx {

    TEST(glob_test, main) {
        Glob challenge;
        std::string given =
                "> BLCKNX \n"
                "PLEASANTLY\n"
                "> BLCKNX \n"
                "MEANLY";
        EXPECT_EQ("8", challenge.main(given));
    }

    TEST(glob_test, calc)
    {
        Glob challenge;
        challenge.model.first = "PLEASANTLY";
        challenge.model.second = "MEANLY";
        challenge.calc();
        EXPECT_EQ(8, challenge.result);
    }

}
