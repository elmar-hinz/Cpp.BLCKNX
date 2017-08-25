//
// Created by Elmar Hinz on 23.08.17.
//

#define protected public

#include "gtest/gtest.h"
#include "Pam250ScoreProvider.h"

TEST(Pam250ScoreProviderTest, table_size) {
    blcknx::Pam250ScoreProvider provider;
    EXPECT_EQ(20, provider.table.size());
    EXPECT_EQ(20, provider.table['A'].size());
}

TEST(Pam250ScoreProviderTest, getScore) {
    blcknx::Pam250ScoreProvider provider;
    EXPECT_EQ(2, provider.getScore('A', 'A'));
    EXPECT_EQ(10, provider.getScore('Y', 'Y'));
    EXPECT_EQ(-3, provider.getScore('A', 'Y'));
    EXPECT_EQ(-3, provider.getScore('Y', 'A'));
    EXPECT_EQ(-2, provider.getScore('M', 'P'));
    EXPECT_EQ(-2, provider.getScore('P', 'M'));
}

TEST(Pam250ScoreProviderTest, getPenalties) {
    blcknx::Pam250ScoreProvider provider;
    EXPECT_EQ(0, provider.getInsertionScore('A'));
    EXPECT_EQ(0, provider.getDeletionScore('A'));
    provider.setGapPenalty(-5);
    EXPECT_EQ(-5, provider.getGapPenalty());
    EXPECT_EQ(-5, provider.getInsertionScore('A'));
    EXPECT_EQ(-5, provider.getDeletionScore('A'));
}

