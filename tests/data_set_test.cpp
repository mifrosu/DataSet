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

//TEST_F(DataSetTest, InitializeDataSet)
//{
    // C++11 version
    // std::vector<std::string> testList = {"ID=1, ... }
//    std::string testArray[] = {"ID=1", "Molecule", "Solubility=2",
//                               "Molecular Weight=2"};
//    std::vector<std::string> testList(testArray, testArray + 4);

//    DataSet testDataSet = DataSet(testList);
//    std::vector<std::string> outList = testDataSet.getHeader();
//    int k = testList.size();
//    for (int i = 0; i < k; ++i)
//    {
//        ASSERT_EQ(testList[i], outList[i]);
//    }

//}
