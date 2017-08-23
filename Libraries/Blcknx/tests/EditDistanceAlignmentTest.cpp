//
// Created by Elmar Hinz on 22.08.17.
//


#include "gtest/gtest.h"

#define protected public

#include "EditDistanceAlignment.h"

namespace blcknx {

    TEST(EditDistanceAlignmentTest, setters_and_getters) {
        EditDistanceAlignment fixture;
        fixture.setStrand1("strand1");
        EXPECT_EQ("strand1", fixture.getStrand1());

        fixture.setStrand2("strand2");
        EXPECT_EQ("strand2", fixture.getStrand2());
    }

    TEST(EditDistanceAlignmentTest, march_match) {
        EditDistanceAlignment fixture;
        std::vector<unsigned long> expected, actual;
        actual = fixture.march("AB", "AB");
        expected = {2, 1, 0};
        EXPECT_EQ(expected, actual);
    }

    TEST(EditDistanceAlignmentTest, march_substiute) {
        EditDistanceAlignment fixture;
        std::vector<unsigned long> expected, actual;
        actual = fixture.march("AA", "BB");
        expected = {2, 2, 2};
        EXPECT_EQ(expected, actual);
    }

    TEST(EditDistanceAlignmentTest, march_insert) {
        EditDistanceAlignment fixture;
        std::vector<unsigned long> expected, actual;
        actual = fixture.march("A", "CA");
        expected = {2, 1};
        EXPECT_EQ(expected, actual);
    }

    TEST(EditDistanceAlignmentTest, march_delete) {
        EditDistanceAlignment fixture;
        std::vector<unsigned long> expected, actual;
        actual = fixture.march("BB", "");
        expected = {0, 1, 2};
        EXPECT_EQ(expected, actual);
    }

    /**
     *     A B
     *   0 1 2
     * A 1 0 1
     * B 2 1 0
     *
     * l | r
     * -----
     * 0 | 1
     * 1 | 0
     * 2 | 1
     */
    TEST(EditDistanceAlignmentTest, meet_match) {
        EditDistanceAlignment fixture;
        fixture.strand1 = "AB";
        fixture.strand2 = "AB";
        std::vector<unsigned long> left = {0, 1, 2};
        std::vector<unsigned long> right = {1, 0, 1};
        EditDistanceAlignment::Meeting actual, expectation;
        actual = fixture.meet(left, right, "AB", 'A');
        expectation = {0, 'A', 'A', "", "B"};
        EXPECT_EQ(actual.distance, expectation.distance);
        EXPECT_EQ(actual.prefix, expectation.prefix);
        EXPECT_EQ(actual.suffix, expectation.suffix);
        EXPECT_EQ(actual.char1, expectation.char1);
        EXPECT_EQ(actual.char2, expectation.char2);
    }

    /**
     *     B A
     *   0 1 2
     * A 1 1 2
     * A 2 2 1
     *
     * l | r
     * -----
     * 0 | 1
     * 1 | 0
     * 2 | 1
     */
    TEST(EditDistanceAlignmentTest, meet_substitute) {
        EditDistanceAlignment fixture;
        fixture.strand1 = "AA";
        fixture.strand2 = "BA";
        std::vector<unsigned long> left = {0, 1, 2};
        std::vector<unsigned long> right = {1, 0, 1};
        EditDistanceAlignment::Meeting actual, expectation;
        actual = fixture.meet(left, right, "AA", 'B');
        expectation = {1, 'A', 'B', "", "A"};
        EXPECT_EQ(actual.distance, expectation.distance);
        EXPECT_EQ(actual.prefix, expectation.prefix);
        EXPECT_EQ(actual.suffix, expectation.suffix);
        EXPECT_EQ(actual.char1, expectation.char1);
        EXPECT_EQ(actual.char2, expectation.char2);
    }

    /**
     *     B A
     *   0 1 1
     * A 1 1 1
     *
     * l | r
     * -----
     * 0 | 0
     * 1 | 1
     */
    TEST(EditDistanceAlignmentTest, meet_insert) {
        EditDistanceAlignment fixture;
        fixture.strand1 = "A";
        fixture.strand2 = "BA";
        std::vector<unsigned long> left = {0, 1};
        std::vector<unsigned long> right = {0, 1};
        EditDistanceAlignment::Meeting actual, expectation;
        actual = fixture.meet(left, right, "A", 'B');
        expectation = {1, '-', 'B', "", "A"};
        EXPECT_EQ(actual.distance, expectation.distance);
        EXPECT_EQ(actual.prefix, expectation.prefix);
        EXPECT_EQ(actual.suffix, expectation.suffix);
        EXPECT_EQ(actual.char1, expectation.char1);
        EXPECT_EQ(actual.char2, expectation.char2);
    }

    /**
     *     A
     *   0 1
     * B 1 1
     * A 2 1
     *
     * l | r
     * -----
     * 0 | 1
     * 1 | 0
     * 2 | 1
     */
    TEST(EditDistanceAlignmentTest, meet_delete) {
        EditDistanceAlignment fixture;
        fixture.strand1 = "BA";
        fixture.strand2 = "A";
        std::vector<unsigned long> left = {0, 1, 2};
        std::vector<unsigned long> right = {1, 0, 1};
        EditDistanceAlignment::Meeting actual, expectation;
        actual = fixture.meet(left, right, "BA", 'A');
        expectation = {1, 'B', 'A', "", "A"};
        EXPECT_EQ(actual.distance, expectation.distance);
        EXPECT_EQ(actual.prefix, expectation.prefix);
        EXPECT_EQ(actual.suffix, expectation.suffix);
        EXPECT_EQ(actual.char1, expectation.char1);
        EXPECT_EQ(actual.char2, expectation.char2);
    }

    /**
     * Preference of substitutions over indel at cost of matches.
     */
    TEST(EditDistanceAlignmentTest, full) {
        EditDistanceAlignment fixture;
        fixture.setStrand1("AABABABB");
        fixture.setStrand2("CCCACACAA");
        fixture.run();
        EXPECT_EQ("AABABAB-B", fixture.getAlignment1());
        EXPECT_EQ("CCCACACAA", fixture.getAlignment2());
        EXPECT_EQ(9, fixture.getAlignmentLength());
        EXPECT_EQ(7, fixture.getAlignmentDistance());
    }
}
