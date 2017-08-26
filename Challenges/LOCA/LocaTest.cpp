//
// Created by Elmar Hinz on 2017-08-24 20:30:21.370955.
//

#include "gtest/gtest.h"

#define protected public
#define private public

#include "Loca.h"

namespace blcknx {

    TEST(loca_test, main) {
        Loca challenge;
        std::string given = "> BLCKNX \n"
                "MEANLYPRTEINSTRING\n"
                "> BLCKNX \n"
                "PLEASANTLYEINSTEIN";
        std::string expected = "23\n"
                "LYPRTEINSTRIN\n"
                "LYEINSTEIN";
        std::string actual = challenge.main(given);
        EXPECT_EQ(expected, actual);
    }
/*
 * 23
 * ASANTLYEINSTEI
 * NX \0INSTRIN
 */
}