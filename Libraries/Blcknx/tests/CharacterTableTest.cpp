//
// Created by Elmar Hinz on 28.08.17.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define protected public

#include "CharacterTable.h"

namespace blcknx {
    TEST(CharacterTableTest, main) {
        std::string newick = "(dog,((elephant_max,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::string table = CharacterTable::to_string(characterTable);
        std::string expectation = "00111\n" "00110\n";
        EXPECT_EQ(expectation, table);
    }

    TEST(CharacterTableTest, tokenize) {
        std::string newick = "(dog,((elephant_max,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::vector<std::string> expectation
                = {"(", "dog", ",", "(", "(", "elephant_max", ",", "mouse", ")",
                   ",", "robot", ")", ",", "cat", ")", ";"};
        EXPECT_EQ(expectation, characterTable.tokens);
    }

    TEST(CharacterTableTest, species) {
        std::string newick = "(dog,((elephant_max,mouse),robot),cat);";
        std::vector<std::string> expectation
                = {"cat", "dog", "elephant_max", "mouse", "robot"};
        CharacterTable characterTable(newick);
        EXPECT_EQ(expectation, characterTable.getSpecies());
    }

    TEST(CharacterTableTest, getTable) {
        std::string newick = "(dog,((elephant_max,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::vector<std::vector<bool>> expectation
                = {{0, 0, 1, 1, 1},
                   {0, 0, 1, 1, 0}};
        EXPECT_EQ(expectation, characterTable.getTable());
    }

    TEST(CharacterTableTest, getIds) {
        std::string newick = "(dog,((elephant_max,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::vector<std::string > expectation = {"00111", "00110"};
        EXPECT_EQ(expectation, characterTable.getCharacterIds());
    }

}
