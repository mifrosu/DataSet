#include "../item.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <iostream>

using namespace mos;

class ItemTest : public ::testing::Test
{
public:
    ItemTest()
    {}

    virtual void SetUp()
    {


    }

    virtual void TearDown()
    {

    }
};

TEST_F(ItemTest, StringColumnPushGetTest)
{
    StringColumn testColumn;
    testColumn.push_back("Hello");
    ASSERT_EQ("Hello", testColumn.getStringDatum(0));
}

TEST_F(ItemTest, IntColumnPushGetTest)
{
    IntColumn testColumn;
    testColumn.push_back(42);
    ASSERT_EQ(42, testColumn.getIntDatum(0));
}

TEST_F(ItemTest, DoubleColumnPushGetTest)
{
    DoubleColumn testColumn;
    testColumn.push_back(2.71828);
    ASSERT_DOUBLE_EQ(2.71828, testColumn.getDoubleDatum(0));
}

TEST_F(ItemTest, StringColumnSizeTest)
{
    StringColumn testColumn;
    testColumn.push_back("Hello");
    testColumn.push_back("Goodbye");
    ASSERT_EQ(2, testColumn.size());
}

TEST_F(ItemTest, IntColumnSizeTest)
{
    IntColumn testColumn;
    testColumn.push_back(42);
    ASSERT_EQ(1, testColumn.size());
}

TEST_F(ItemTest, DoubleColumnSizeTest)
{
    DoubleColumn testColumn;
    testColumn.push_back(2.71828);
    testColumn.push_back(3.14159);
    testColumn.push_back(8.31451);
    ASSERT_EQ(3, testColumn.size());
}
