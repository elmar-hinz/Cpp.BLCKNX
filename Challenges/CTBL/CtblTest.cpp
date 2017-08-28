//
// Created by Elmar Hinz on 2017-08-28 15:59:33.048502.
//

#include "gtest/gtest.h"
#define protected public
#define private public
#include "Ctbl.h"

namespace blcknx {

    TEST(ctbl_test, main)
    {
        Ctbl challenge;
        std::string given = "(dog,((elephant,mouse),robot),cat);";
        std::string expected = "00110\n" "00111\n";
        EXPECT_EQ(expected, challenge.main(given));
    }        

}