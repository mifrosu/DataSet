#include "../data_set.h"
#include <gtest/gtest.h>

using namespace mos_dataset;

class DataSetTest : public ::testing::Test
{
    DataSetTest()
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
