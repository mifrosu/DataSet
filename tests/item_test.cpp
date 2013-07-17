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
    ASSERT_EQ("Hello", testColumn.getDatum(0));
}

TEST_F(ItemTest, IntColumnPushGetTest)
{
    IntColumn testColumn;
    testColumn.push_back(42);
    ASSERT_EQ(42, testColumn.getDatum(0));
}

TEST_F(ItemTest, DoubleColumnPushGetTest)
{
    DoubleColumn testColumn;
    testColumn.push_back(2.71828);
    ASSERT_DOUBLE_EQ(2.71828, testColumn.getDatum(0));
}
