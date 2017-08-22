//
// Created by Elmar Hinz on 19.08.17.
//

#include "gtest/gtest.h"

#define protected public
#include "Challenge.h"

class ChallengeTest : public ::testing::Test {
protected:
    blcknx::Challenge * challenge;

    void SetUp() {
        challenge = new blcknx::Challenge();
    }

    void TearDown() {
        delete challenge;
    }
};


TEST_F(ChallengeTest, main_returns_empty_string_by_default)
{
    blcknx::Challenge challenge;
    std::string actual = challenge.main("input");
    EXPECT_EQ("", actual);
}

TEST_F(ChallengeTest, main_returns_protected_output)
{
    challenge->output = "output";
    std::string actual = challenge->main("input");
    EXPECT_EQ("output", actual);
}


