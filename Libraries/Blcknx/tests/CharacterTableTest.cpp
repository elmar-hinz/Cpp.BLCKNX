//
// Created by Elmar Hinz on 28.08.17.
//

#include "gtest/gtest.h"

#define protected public

#include "CharacterTable.h"

namespace blcknx {
    TEST(CharacterTableTest, main) {
        std::string newick = "(dog,((elephant,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::string table = CharacterTable::to_string(characterTable);
        std::string expectation = "00110\n" "00111\n";
        EXPECT_EQ(expectation, table);
    }

    TEST(CharacterTableTest, tokenize) {
        std::string newick = "(dog,((elephant,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::vector<std::string> expectation
                = {"(", "dog", ",", "(", "(", "elephant", ",", "mouse", ")",
                   ",", "robot", ")", ",", "cat", ")", ";"};
        EXPECT_EQ(expectation, characterTable.tokens);
    }

    TEST(CharacterTableTest, species) {
        std::string newick = "(dog,((elephant,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::map<std::string, unsigned long> expectation;
        expectation["cat"] = 0;
        expectation["dog"] = 1;
        expectation["elephant"] = 2;
        expectation["mouse"] = 3;
        expectation["robot"] = 4;
        EXPECT_EQ(expectation, characterTable.species);
    }

    TEST(CharacterTableTest, table) {
        std::string newick = "(dog,((elephant,mouse),robot),cat);";
        CharacterTable characterTable(newick);
        std::vector<std::vector<bool>> expectation
                = {{0, 0, 1, 1, 0},
                   {0, 0, 1, 1, 1}};
        EXPECT_EQ(expectation, characterTable.table);
    }

}
