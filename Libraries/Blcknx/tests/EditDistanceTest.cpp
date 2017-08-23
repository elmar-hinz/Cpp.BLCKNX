//
// Created by Elmar Hinz on 23.08.17.
//

#include "gtest/gtest.h"

#define protected public

#include "EditDistance.h"

namespace blcknx {
    TEST(EditDistanceTest, zeor) {
        unsigned long expected, actual;
        expected = 0;
        actual = EditDistance::measure("", "");
        ASSERT_EQ(expected, actual);
    }

    TEST(EditDistanceTest, match) {
        ASSERT_EQ(0, EditDistance::measure("A", "A"));
        ASSERT_EQ(0, EditDistance::measure("AB", "AB"));
    }

    TEST(EditDistanceTest, substitute) {
        ASSERT_EQ(1, EditDistance::measure("A", "C"));
        ASSERT_EQ(1, EditDistance::measure("AB", "AC"));
        ASSERT_EQ(1, EditDistance::measure("BA", "CA"));
        ASSERT_EQ(1, EditDistance::measure("ABA", "ACA"));
        ASSERT_EQ(2, EditDistance::measure("AA", "CC"));
        ASSERT_EQ(2, EditDistance::measure("ABBA", "ACCA"));
    }

    TEST(EditDistanceTest, insert) {
        ASSERT_EQ(1, EditDistance::measure("A", "CA"));
        ASSERT_EQ(1, EditDistance::measure("A", "AC"));
        ASSERT_EQ(2, EditDistance::measure("A", "CAC"));
    }
}
