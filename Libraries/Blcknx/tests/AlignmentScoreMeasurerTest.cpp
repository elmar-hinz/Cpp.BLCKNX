//
// Created by Elmar Hinz on 23.08.17.
//

#include "gtest/gtest.h"

#define protected public

#include "AlignmentScoreMeasurer.h"
#include "LongestCommenSubsequenceScoreProvider.h"
#include "Pam250ScoreProvider.h"

namespace blcknx {
    class AlignmentScoreMeasurerTest : public ::testing::Test {
    public:
        class Provider : public LongestCommenSubsequenceScoreProvider {
        };

        Provider provider;
        AlignmentScoreMeasurer measurer;

    protected:

        void SetUp() override {
            Provider e;
            provider = std::move(e);
            AlignmentScoreMeasurer m;
            measurer = std::move(m);
            measurer.setScoreProvider(&provider);
        }

    };

    TEST_F(AlignmentScoreMeasurerTest, gettersAndSetters) {
        EXPECT_EQ(&provider, measurer.getScoreProvider());
        measurer.setStrand1("S1");
        measurer.setStrand2("S2");
        EXPECT_EQ("S1", measurer.getStrand1());
        EXPECT_EQ("S2", measurer.getStrand2());
    }

    TEST_F(AlignmentScoreMeasurerTest, freeRides) {
        EXPECT_EQ(measurer.NoFreeRides, measurer.getFreeRideDimensions());
        measurer.setFreeRideDimensions(measurer.HalfFreeRides);
        EXPECT_EQ(measurer.HalfFreeRides, measurer.getFreeRideDimensions());
        measurer.setFreeRideDimensions(measurer.FullFreeRides);
        EXPECT_EQ(measurer.FullFreeRides, measurer.getFreeRideDimensions());
    }

    TEST_F(AlignmentScoreMeasurerTest, finalDeletions) {
        EXPECT_TRUE(measurer.hasFinalDeletions());
        measurer.disableFinalDeletions();
        EXPECT_FALSE(measurer.hasFinalDeletions());
        measurer.enableFinalDeletions();
        EXPECT_TRUE(measurer.hasFinalDeletions());
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


    class AlignmentScoreMeasurerTest2 : public ::testing::Test {
    public:
        Pam250ScoreProvider provider;
        AlignmentScoreMeasurer measurer;

    protected:

        void SetUp() override {
            Pam250ScoreProvider e;
            provider = std::move(e);
            provider.setGapPenalty(-5);
            AlignmentScoreMeasurer m;
            measurer = std::move(m);
            measurer.setScoreProvider(&provider);
        }
    };

    TEST_F(AlignmentScoreMeasurerTest2, global_alignment) {
        measurer.setStrand1("MEANLYPRTEINSTRING");
        measurer.setStrand2("PLEASANTLYEINSTEIN");
        measurer.measure();
        EXPECT_EQ(13, measurer.getScore());
        AlignmentScoreMeasurer::BestScore best;
        best = measurer.getBestScore();
        EXPECT_EQ(18, best.score);
    }

    TEST_F(AlignmentScoreMeasurerTest2, full_free_rides) {
        measurer.setStrand1("MEANLYPRTEINSTRINGS");
        measurer.setStrand2("PLEASANTLYEINSTEINISDEAD");
        measurer.setFreeRideDimensions(measurer.FullFreeRides);
        measurer.measure();
        AlignmentScoreMeasurer::BestScore best = measurer.getBestScore();
        EXPECT_EQ(23, best.score);
        EXPECT_EQ(17, best.index1);
        EXPECT_EQ(18, best.index2);

    }

    TEST_F(AlignmentScoreMeasurerTest2, border_free_rides) {
        measurer.setStrand1("MEANLYPRTEINSTRINGS");
        measurer.setStrand2("PLEASANTLYEINSTEINISDEAD");
        measurer.setFreeRideDimensions(measurer.HalfFreeRides);
        measurer.measure();
        AlignmentScoreMeasurer::BestScore best = measurer.getBestScore();
        EXPECT_EQ(18, best.score);
        EXPECT_EQ(17, best.index1);
        EXPECT_EQ(18, best.index2);
    }

    TEST_F(AlignmentScoreMeasurerTest2, final_deletion) {
        measurer.setStrand1("YYPP");
        measurer.setStrand2("YY");
        measurer.measure();
        std::vector<long> expectation = {-10, 5, 20, 15, 10};
        EXPECT_EQ(expectation, measurer.getFront());
        measurer.disableFinalDeletions();
        measurer.measure();
        expectation = {-10, 5, 20, 0, -5};
        EXPECT_EQ(expectation, measurer.getFront());
    }
}
