//
// Created by Elmar Hinz on 23.08.17.
//

#include "gtest/gtest.h"

#define protected public

#include "AlignmentScoreMeasurer.h"
#include "LongestCommenSubsequenceScoreEvaluator.h"


namespace blcknx {
    class AlignmentScoreMeasurerTest : public ::testing::Test {
    public:
        class Evaluator : public LongestCommenSubsequenceScoreEvaluator {};
        Evaluator evaluator;
        AlignmentScoreMeasurer measurer;

    protected:

        void SetUp() override {
            Evaluator e;
            evaluator = std::move(e);
            AlignmentScoreMeasurer m;
            measurer = std::move(m);
            measurer.setScoreEvaluator(&evaluator);
        }

    };

    TEST_F(AlignmentScoreMeasurerTest, getters) {
        EXPECT_EQ(&evaluator, measurer.getScoreEvaluator());
        measurer.setStrand1("S1");
        measurer.setStrand2("S2");
        EXPECT_EQ("S1", measurer.getStrand1());
        EXPECT_EQ("S2", measurer.getStrand2());
    }

    TEST_F(AlignmentScoreMeasurerTest, zero) {
        EXPECT_EQ(0, measurer.measure("", ""));
    }

    TEST_F(AlignmentScoreMeasurerTest, match) {
        EXPECT_EQ(1, measurer.measure("A", "A"));
        EXPECT_EQ(2, measurer.measure("AB", "AB"));
    }

    TEST_F(AlignmentScoreMeasurerTest, replace) {
        EXPECT_EQ(0, measurer.measure("A", "B"));
        EXPECT_EQ(0, measurer.measure("AA", "BB"));
        EXPECT_EQ(2, measurer.measure("ABBA", "ACCA"));
    }

    TEST_F(AlignmentScoreMeasurerTest, insert) {
        EXPECT_EQ(1, measurer.measure("A", "CA"));
        EXPECT_EQ(1, measurer.measure("A", "AC"));
        EXPECT_EQ(1, measurer.measure("A", "CAC"));
    }

    TEST_F(AlignmentScoreMeasurerTest, full) {
        measurer.setStrand1("AB");
        measurer.setStrand2("AD");
        measurer.measure();
        EXPECT_EQ(1, measurer.getScore());
        EXPECT_EQ(std::vector<long>({0, 1, 1}), measurer.getFront());
    }
}
