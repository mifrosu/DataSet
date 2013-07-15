#include "../split_string.h"
#include <gtest/gtest.h>

using namespace mos_dataset;

class SplitStringTest : public ::testing::Test
{
public:
    SplitStringTest()
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

TEST_F(SplitStringTest, SplitTabSeparated)
{
    std::string testLine("hello\tWorld!");
    std::vector<std::string> testStore;
    split(testLine, &testStore);
    if (testStore.size() > 1) {
        // to avoid a crash if split() fails to push > 1 string to the store
        ASSERT_EQ("hello", testStore[0]);
        ASSERT_EQ("World!", testStore[1]);
    }
    else {

        ASSERT_EQ(2, testStore.size());
    }
}
