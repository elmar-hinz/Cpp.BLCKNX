//
// Created by Elmar Hinz on 23.08.17.
//

#include "gtest/gtest.h"
#include "LongestCommenSubsequenceScoreEvaluator.h"

TEST(LongestCommenSubsequenceScoreEvaluatorTest, full)
{
    EXPECT_EQ(1, 1);
    blcknx::LongestCommenSubsequenceScoreEvaluator evaluator;
    EXPECT_EQ(1, evaluator.getScore('A', 'A'));
    EXPECT_EQ(0, evaluator.getScore('A', 'Y'));
    EXPECT_EQ(0, evaluator.getScore('Y', 'A'));
}

TEST(LongestCommenSubsequenceScoreEvaluatorTest, getPenalties) {
    blcknx::LongestCommenSubsequenceScoreEvaluator evaluator;
    EXPECT_EQ(0, evaluator.getInsertionScore('A'));
    EXPECT_EQ(0, evaluator.getDeletionScore('A'));
}
