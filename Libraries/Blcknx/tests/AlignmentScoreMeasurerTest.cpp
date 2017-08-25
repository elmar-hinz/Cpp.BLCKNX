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
            measurer.enableMatrix();
        }
    };

    TEST_F(AlignmentScoreMeasurerTest, getters) {
        EXPECT_EQ(&provider, measurer.getScoreProvider());
        measurer.setStrand1("S1");
        measurer.setStrand2("S2");
        EXPECT_EQ("S1", measurer.getStrand1());
        EXPECT_EQ("S2", measurer.getStrand2());
    }

    TEST_F(AlignmentScoreMeasurerTest, freeRide_switching) {
        EXPECT_FALSE(measurer.hasFreeRides());
        measurer.enableFreeRides();
        EXPECT_TRUE(measurer.hasFreeRides());
        measurer.disableFreeRides();
        EXPECT_FALSE(measurer.hasFreeRides());
    }

    TEST_F(AlignmentScoreMeasurerTest, zero) {
        EXPECT_EQ(0, measurer.measure("", ""));
        EXPECT_EQ(1, measurer.matrix.size());
    }

    TEST_F(AlignmentScoreMeasurerTest, matrix_switching) {
        measurer.disableMatrix();
        EXPECT_FALSE(measurer.hasMatrix());
        EXPECT_EQ(1, measurer.measure("A", "A"));
        EXPECT_EQ(0, measurer.matrix.size());
        measurer.enableMatrix();
        EXPECT_TRUE(measurer.hasMatrix());
        EXPECT_EQ(1, measurer.measure("A", "A"));
        EXPECT_EQ(2, measurer.matrix.size());
        EXPECT_EQ(2, measurer.matrix[1].size());
    }

    TEST_F(AlignmentScoreMeasurerTest, match) {
        EXPECT_EQ(1, measurer.measure("A", "A"));
        EXPECT_EQ(2, measurer.matrix.size());
        EXPECT_EQ(1, measurer.matrix[1][1].score);
        EXPECT_EQ(0, measurer.matrix[1][1].backPointer.first);
        EXPECT_EQ(0, measurer.matrix[1][1].backPointer.second);
        EXPECT_EQ(2, measurer.measure("AB", "AB"));
        EXPECT_EQ(3, measurer.matrix.size());
        EXPECT_EQ(2, measurer.matrix[2][2].score);
        EXPECT_EQ(1, measurer.matrix[2][2].backPointer.first);
        EXPECT_EQ(1, measurer.matrix[2][2].backPointer.second);
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
        EXPECT_EQ(3, measurer.matrix.size());
        EXPECT_EQ(1, measurer.matrix[2][1].score);
        EXPECT_EQ(1, measurer.matrix[2][1].backPointer.first);
        EXPECT_EQ(1, measurer.matrix[2][1].backPointer.second);
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
            measurer.enableMatrix();
        }
    };

    TEST_F(AlignmentScoreMeasurerTest2, full) {
        measurer.setStrand1("MEANLYPRTEINSTRING");
        measurer.setStrand2("PLEASANTLYEINSTEIN");
        measurer.measure();
        measurer.enableFreeRides();
        measurer.enableMatrix();
        measurer.measure();
//        std::cerr << measurer.debugMatrix() << std::endl;
        EXPECT_EQ(18, measurer.getScore());
        auto winner = measurer.findMatrixWinner();
//        std::cerr << measurer.debugMatrixCell(winner) << std::endl;
        EXPECT_EQ(23, winner.score);
        EXPECT_EQ(17, winner.address.first);
        EXPECT_EQ(18, winner.address.second);
        EXPECT_EQ(16, winner.backPointer.first);
        EXPECT_EQ(17, winner.backPointer.second);
        auto backtrack = measurer.backtrack(winner);
        EXPECT_EQ("LYEINSTIN", backtrack.common);
        EXPECT_EQ("LYPRTEINSTRIN", backtrack.strand1);
        EXPECT_EQ("LYEINSTEIN", backtrack.strand2);
        EXPECT_EQ("LYPRTEINSTRIN", backtrack.alignment1);
        EXPECT_EQ("LY---EINSTEIN", backtrack.alignment2);
    }

}
