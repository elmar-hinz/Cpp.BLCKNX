//
// Created by Elmar Hinz on 2017-08-28 10:21:39.603976.
//

#include "gtest/gtest.h"
#define protected public
#define private public
#include "Root.h"

namespace blcknx {

    TEST(cunr_test, build) {
        Root challenge;
        challenge.setInput("5");
        challenge.build();
        EXPECT_EQ(5, challenge.model);
    }

    TEST(cunr_test, format) {
        Root challenge;
        challenge.result = 15;
        challenge.format();
        EXPECT_EQ("15", challenge.getOutput());
    }

    TEST(root_test, main)
    {
        Root challenge;
        std::string given = "4";
        std::string expected = "15";
        EXPECT_EQ(expected, challenge.main(given));
    }        

}