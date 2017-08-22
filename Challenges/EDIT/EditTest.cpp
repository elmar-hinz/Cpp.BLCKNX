//
// Created by Elmar Hinz on 21.08.17.
//

#include "gtest/gtest.h"
#define protected public
#include "Edit.h"

TEST(edit_test, main)
{
    Edit challenge;
    std::string given = ">xxx \nPLEASANTLY\n>xxx \nMEANLY";
    std::string expected = "5";
    EXPECT_EQ(expected, challenge.main(given));
}

TEST(edit_test, edit_distance_match)
{
    Edit challenge;
    std::pair<std::string, std::string> given = {"A", "A"};
    unsigned expected = 0;
    unsigned actual = challenge.edit_distance(given.first, given.second);
    EXPECT_EQ(expected, actual);
}

TEST(edit_test, edit_distance_substitution)
{
    Edit challenge;
    std::pair<std::string, std::string> given = {"A", "B"};
    unsigned expected = 1;
    unsigned actual = challenge.edit_distance(given.first, given.second);
    EXPECT_EQ(expected, actual);
}

TEST(edit_test, edit_distance1)
{
    Edit challenge;
    std::pair<std::string, std::string> given = {"PLEASANTLY", "MEANLY"};
    unsigned expected = 5;
    unsigned actual = challenge.edit_distance(given.first, given.second);
    EXPECT_EQ(expected, actual);

}

