//
// Created by Elmar Hinz on 2017-08-28 09:53:58.152865.
//

#include "gtest/gtest.h"

#define protected public
#define private public

#include "Cunr.h"

namespace blcknx {

    TEST(cunr_test, build) {
        Cunr challenge;
        challenge.setInput("5");
        challenge.build();
        EXPECT_EQ(5, challenge.model);
    }

    TEST(cunr_test, format) {
        Cunr challenge;
        challenge.result = 15;
        challenge.format();
        EXPECT_EQ("15", challenge.getOutput());
    }

    TEST(cunr_test, main) {
        Cunr challenge;
        std::string given = "5";
        std::string expected = "15";
        EXPECT_EQ(expected, challenge.main(given));
    }

}