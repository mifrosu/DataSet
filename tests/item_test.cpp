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

TEST_F(ItemTest, FindStringIndexes)
{
    std::string testArray[] = {"to", "be", "or", "not", "to", "be"};
    StringColumn testColumn;
    for (int i=0; i != 6; ++i) {
        testColumn.push_back(testArray[i]);
    }
    std::vector<unsigned int> indexList;
    indexList = testColumn.findValue("to");
    std::vector<unsigned int> expectedList = {0, 4};
    ASSERT_EQ(2, indexList.size());
    ASSERT_EQ(expectedList, indexList);
}

TEST_F(ItemTest, FindIntIndexes)
{
    int testArray[] = {2, 9, 2, 9, 9, 9};
    IntColumn testColumn;
    for (int i=0; i != 6; ++i) {
        testColumn.push_back(testArray[i]);
    }
    std::vector<unsigned int> indexList;
    indexList = testColumn.findValue(9);
    std::vector<unsigned int> expectedList = {1, 3, 4, 5};
    ASSERT_EQ(4, indexList.size());
    ASSERT_EQ(expectedList, indexList);
}

TEST_F(ItemTest, FindDoubleIndexes)
{
    double testArray[] = {2.0, 9.0001, 2.0, 9.0002, 9.0001, 9.0001};
    DoubleColumn testColumn;
    for (int i=0; i != 6; ++i) {
        testColumn.push_back(testArray[i]);
    }
    std::vector<unsigned int> indexList;
    indexList = testColumn.findValue(9.0001);
    std::vector<unsigned int> expectedList = {1, 4, 5};
    ASSERT_EQ(3, indexList.size());
    ASSERT_EQ(expectedList, indexList);
}

TEST_F(ItemTest, UniqueStringPlanTest)
{
    std::string testArray[] = {"to", "be", "or", "not", "to", "be"};
    StringColumn testColumn;
    for (int i=0; i != 6; ++i) {
        testColumn.push_back(testArray[i]);
    }
    std::vector<char> testPlan = testColumn.getUniquePlan();
    std::vector<char> expectPlan = {'n', 'n', 'y', 'y', 'y', 'y'};
    ASSERT_EQ(6, testPlan.size());
    ASSERT_EQ(expectPlan, testPlan);
}

TEST_F(ItemTest, UniqueIntPlanTest)
{
    int testArray[] = {2, 9, 2, 9, 9, 9};
    IntColumn testColumn;
    for (int i=0; i != 6; ++i) {
        testColumn.push_back(testArray[i]);
    }
    std::vector<char> testPlan = testColumn.getUniquePlan();
    std::vector<char> expectPlan = {'n', 'n', 'y', 'n', 'n', 'y'};
    ASSERT_EQ(6, testPlan.size());
    ASSERT_EQ(expectPlan, testPlan);
}

TEST_F(ItemTest, UniqueDoublePlanTest)
{
    double testArray[] = {2.0, 9.0001, 2.0, 9.0002, 9.0001, 9.0001};
    DoubleColumn testColumn;
    for (int i=0; i != 6; ++i) {
        testColumn.push_back(testArray[i]);
    }
    std::vector<char> testPlan = testColumn.getUniquePlan();
    std::vector<char> expectPlan = {'n', 'n', 'y', 'y', 'n', 'y'};
    ASSERT_EQ(6, testPlan.size());
    ASSERT_EQ(expectPlan, testPlan);
}


