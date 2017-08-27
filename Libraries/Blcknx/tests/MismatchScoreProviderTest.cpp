//
// Created by Elmar Hinz on 27.08.17.
//

#include "gtest/gtest.h"
#include "MismatchScoreProvider.h"

TEST(MismatchScoreProviderTest, indels)
{
    blcknx::MismatchScoreProvider provider;
    EXPECT_EQ(-1, provider.getDeletionScore('A'));
    EXPECT_EQ(-1, provider.getInsertionScore('A'));
}

TEST(MismatchScoreProviderTest, matches)
{
    blcknx::MismatchScoreProvider provider;
    EXPECT_EQ(1, provider.getScore('A', 'A'));
    EXPECT_EQ(-1, provider.getScore('A', 'Y'));
    EXPECT_EQ(-1, provider.getScore('Y', 'A'));
}