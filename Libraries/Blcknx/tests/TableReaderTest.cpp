//
// Created by Elmar Hinz on 25.08.17.
//

#include "gtest/gtest.h"
#include "TableReader.h"

namespace blcknx {


    class TableReaderFixture : public ::testing::Test {
    public:
        std::string tableDefinition;
        std::map<char, std::map<char, int>> table;

    protected:
        void SetUp() override {
            tableDefinition = "- A B C\n"
                    "A 1 -2 -3\n"
                    "B 2  4 -7\n"
                    "C 3  7 14";
        }
    };

    TEST_F(TableReaderFixture, table_size) {
        TableReader::read(tableDefinition, table);
        EXPECT_EQ(3, table.size());
        EXPECT_EQ(3, table['C'].size());
    }

    TEST_F(TableReaderFixture, value_access) {
        TableReader::read(tableDefinition, table);
        EXPECT_EQ(1, table['A']['A']);
        EXPECT_EQ(14, table['C']['C']);
        EXPECT_EQ(-7, table['B']['C']);
        EXPECT_EQ(+7, table['C']['B']);
    }
}
