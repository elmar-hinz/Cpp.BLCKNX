//
// Created by Elmar Hinz on 23.08.17.
//

#define protected public

#include "gtest/gtest.h"
#include "Blosum62ScoreEvaluator.h"

TEST(Blosum62ScoreEvaluatorTest, table_size) {
    blcknx::Blosum62ScoreEvaluator evaluator;
    EXPECT_EQ(20, evaluator.table.size());
    EXPECT_EQ(20, evaluator.table['A'].size());
}

TEST(Blosum62ScoreEvaluatorTest, getScore) {
    blcknx::Blosum62ScoreEvaluator evaluator;
    EXPECT_EQ(4, evaluator.getScore('A', 'A'));
    EXPECT_EQ(7, evaluator.getScore('Y', 'Y'));
    EXPECT_EQ(-2, evaluator.getScore('A', 'Y'));
    EXPECT_EQ(-2, evaluator.getScore('Y', 'A'));
    EXPECT_EQ(-2, evaluator.getScore('M', 'P'));
    EXPECT_EQ(-2, evaluator.getScore('P', 'M'));
}

TEST(Blosum62ScoreEvaluatorTest, getPenalties) {
    blcknx::Blosum62ScoreEvaluator evaluator;
    EXPECT_EQ(0, evaluator.getInsertionScore('A'));
    EXPECT_EQ(0, evaluator.getDeletionScore('A'));
    evaluator.setGapPenalty(-5);
    EXPECT_EQ(-5, evaluator.getGapPenalty());
    EXPECT_EQ(-5, evaluator.getInsertionScore('A'));
    EXPECT_EQ(-5, evaluator.getDeletionScore('A'));
}

