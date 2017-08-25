//
// Created by Elmar Hinz on 24.08.17.
//

#include "gtest/gtest.h"
#include "EditDistanceScoreProvider.h"

TEST(EditDistanceScoreProviderTest, indels)
{
    blcknx::EditDistanceScoreProvider provider;
    EXPECT_EQ(-1, provider.getDeletionScore('A'));
    EXPECT_EQ(-1, provider.getInsertionScore('A'));
}

TEST(EditDistanceScoreProviderTest, matches)
{
    blcknx::EditDistanceScoreProvider provider;
    EXPECT_EQ(0, provider.getScore('A', 'A'));
    EXPECT_EQ(-1, provider.getScore('A', 'Y'));
    EXPECT_EQ(-1, provider.getScore('Y', 'A'));
}