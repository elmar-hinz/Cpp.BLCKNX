//
// Created by Elmar Hinz on 23.08.17.
//

#include "gtest/gtest.h"
#include "LongestCommenSubsequenceScoreProvider.h"

TEST(LongestCommenSubsequenceScoreProviderTest, full)
{
    blcknx::LongestCommenSubsequenceScoreProvider provider;
    EXPECT_EQ(1, provider.getScore('A', 'A'));
    EXPECT_EQ(0, provider.getScore('A', 'Y'));
    EXPECT_EQ(0, provider.getScore('Y', 'A'));
}

TEST(LongestCommenSubsequenceScoreProviderTest, getPenalties) {
    blcknx::LongestCommenSubsequenceScoreProvider provider;
    EXPECT_EQ(0, provider.getInsertionScore('A'));
    EXPECT_EQ(0, provider.getDeletionScore('A'));
}
