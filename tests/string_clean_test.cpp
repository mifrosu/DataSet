#include "../data_set.h"
#include <string>
#include <vector>
#include <gtest/gtest.h>

using namespace mos;

class StringCleanTest : public ::testing::Test
{
public:
    StringCleanTest()
    {}

    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

/**
  * Tests:
  *
  * Initialize function:
  * * input line creates a std::vector<std::string> list that acts as index id
  * * initializes dataSet vector with correct derived pointers
  * * i.e. column header
  * Read subsequent lines to create entries
  *
  */

TEST_F(StringCleanTest, SplitTabSeparated)
{
    std::string testLine = "hello\tWorld!";
    std::vector<std::string> testStore;
    split(testLine, &testStore);
    ASSERT_EQ(2, testStore.size());
    ASSERT_EQ("hello", testStore[0]);
    ASSERT_EQ("World!", testStore[1]);
}

TEST_F(StringCleanTest, SplitCommanSeparated)
{
    std::string testLine = "hello, World!";
    std::vector<std::string> testStore;
    split(testLine, &testStore, ",");
    ASSERT_EQ(2, testStore.size());
    ASSERT_EQ("hello", testStore[0]);
    ASSERT_EQ("World!", testStore[1]);
}

TEST_F(StringCleanTest, StripWhiteSpace)
{
    std::string testString = " test test    ";
    strip(&testString);
    ASSERT_EQ("test test", testString);
}
