//
// Created by Elmar Hinz on 2017-08-29 11:10:13.427990.
//

#include "gtest/gtest.h"

#define protected public
#define private public

#include "Sptd.h"

namespace blcknx {
    TEST(sptd_test, build) {
        Sptd challenge;
        challenge.input = "one\ntwo\nthree\n";
        challenge.build();
        EXPECT_EQ("two", challenge.model.first);
        EXPECT_EQ("three", challenge.model.second);
    }

    TEST(sptd_test, format) {
        Sptd challenge;
        challenge.input = "one\ntwo\nthree\n";
        challenge.result = 2;
        challenge.format();
        EXPECT_EQ("2", challenge.output);
    }

    TEST(sptd_test, main) {
        Sptd challenge;
        std::string given = "dog rat elephant mouse cat rabbit\n"
                "(rat,(dog,cat),(rabbit,(elephant,mouse)));\n"
                "(rat,(cat,dog),(elephant,(mouse,rabbit)));";
        std::string expected = "2";
        EXPECT_EQ(expected, challenge.main(given));
    }

}