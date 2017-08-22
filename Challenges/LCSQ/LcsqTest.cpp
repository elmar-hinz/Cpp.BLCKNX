//
// Created by Elmar Hinz on 20.08.17.
//

#define private public
#define protected public

#include "gtest/gtest.h"
#include "Lcsq.h"

TEST(lcsq_test, longest_common_sequence) {
    Lcsq challenge;
    std::string strand1 = "AACCTTGG";
    std::string strand2 = "ACACTGTGA";
    std::string expect = "ACCTGG";
    std::string actual = challenge.longest_common_subsequence(strand1, strand2);
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, align__empty_first) {
    Lcsq challenge;
    Lcsq::Alignment expect = {0, "--", "AB"};
    Lcsq::Alignment actual = challenge.align("", "AB");
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, align__empty_second) {
    Lcsq challenge;
    Lcsq::Alignment expect = {0, "AB", "--"};
    Lcsq::Alignment actual = challenge.align("AB", "");
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, align__some_substitutions) {
    Lcsq challenge;
    Lcsq::Alignment expect = {2, "ACAT", "AGAG"};
    Lcsq::Alignment actual = challenge.align("ACAT", "AGAG");
    EXPECT_EQ(expect, actual);
    EXPECT_EQ(expect.strand1, actual.strand1);
    EXPECT_EQ(expect.strand2, actual.strand2);
}

TEST(lcsq_test, split__one) {
    Lcsq challenge;
    Lcsq::Splitting expect = {"", 'A', ""};
    Lcsq::Splitting actual = challenge.split("A");
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, split__odd) {
    Lcsq challenge;
    Lcsq::Splitting expect = {"AB", 'C', "DE"};
    Lcsq::Splitting actual = challenge.split("ABCDE");
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, split__even) {
    Lcsq challenge;
    Lcsq::Splitting expect = {"AB", 'C', "D"};
    Lcsq::Splitting actual = challenge.split("ABCD");
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, march__match) {
    Lcsq challenge;
    std::string strand1 = "A";
    std::string strand2 = "A";
    std::vector<unsigned> expect = {0, 1};
    std::vector<unsigned> actual = challenge.march(strand1, strand2);
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, march__double_match) {
    Lcsq challenge;
    std::string strand1 = "AA";
    std::string strand2 = "AA";
    std::vector<unsigned> expect = {0, 1, 2};
    std::vector<unsigned> actual = challenge.march(strand1, strand2);
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, march__substitution) {
    Lcsq challenge;
    std::string strand1 = "A";
    std::string strand2 = "B";
    std::vector<unsigned> expect = {0, 0};
    std::vector<unsigned> actual = challenge.march(strand1, strand2);
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, march__deletion) {
    Lcsq challenge;
    std::string strand1 = "AB";
    std::string strand2 = "A";
    std::vector<unsigned> expect = {0, 1, 1};
    std::vector<unsigned> actual = challenge.march(strand1, strand2);
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, march__insertion) {
    Lcsq challenge;
    std::string strand1 = "A";
    std::string strand2 = "AB";
    std::vector<unsigned> expect = {0, 1};
    std::vector<unsigned> actual = challenge.march(strand1, strand2);
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, meet__minimal) {
    Lcsq challenge;
    Lcsq::Meeting actual = challenge.meet({0}, {0}, "", 'A');
    Lcsq::Meeting expect = {0, '-', 'A', "", ""};
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, meet__match) {
    Lcsq challenge;
    Lcsq::Meeting actual = challenge.meet({1, 1}, {1, 1}, "A", 'A');
    Lcsq::Meeting expect = {3, 'A', 'A', "", ""};
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, meet__substitute) {
    Lcsq challenge;
    Lcsq::Meeting actual = challenge.meet({0, 0}, {0, 0}, "A", 'B');
    Lcsq::Meeting expect = {0, 'A', 'B', "", ""};
    EXPECT_EQ(expect, actual);
}

TEST(lcsq_test, reversed) {
    Lcsq challenge;
    std::string given = "AB";
    std::string actual = challenge.reversed(given);
    EXPECT_EQ("BA", actual);
    EXPECT_EQ("AB", given);
}
