//
// Created by Elmar Hinz on 24.08.17.
//

#include "gtest/gtest.h"
#include "EditDistanceScoreEvaluator.h"

TEST(EditDistanceScoreEvaluatorTest, indels)
{
    blcknx::EditDistanceScoreEvaluator evaluator;
    EXPECT_EQ(-1, evaluator.getDeletionScore('A'));
    EXPECT_EQ(-1, evaluator.getInsertionScore('A'));
}

TEST(EditDistanceScoreEvaluatorTest, matches)
{
    blcknx::EditDistanceScoreEvaluator evaluator;
    EXPECT_EQ(0, evaluator.getScore('A', 'A'));
    EXPECT_EQ(-1, evaluator.getScore('A', 'Y'));
    EXPECT_EQ(-1, evaluator.getScore('Y', 'A'));
}