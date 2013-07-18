#include "../data_set.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <iostream>

using namespace mos;

class DataSetTest : public ::testing::Test
{
public:
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

TEST_F(DataSetTest, InitializeHeader)
{
//     C++11 version
//     std::vector<std::string> testList = {"ID=1, ... }
    std::string testFile = "test_file.txt";
    std::string testHead = "ID=1, Molecule, Solubility=2, Molecular Weight=2";

    std::ofstream testFileStream(testFile.c_str());
    if (!testFileStream) {
        FAIL();
    }
    testFileStream << testHead << std::endl;
    testFileStream.close();

    DataSet testDataSet = DataSet(testFile,",");

    std::vector<std::string> testOutHeader = testDataSet.getHeader();
    testDataSet.displaySet(std::cout,",");

    ASSERT_EQ("UNIQUE_KEY=1", testOutHeader[0]);
    ASSERT_EQ("ID=1", testOutHeader[1]);
    ASSERT_EQ("Molecule", testOutHeader[2]);
    ASSERT_EQ("Solubility=2", testOutHeader[3]);
    ASSERT_EQ("Molecular Weight=2", testOutHeader[4]);

    int returnCode = std::remove(testFile.c_str());
    if (returnCode != 0) {
        FAIL();
    }


//    DataSet testSet = DataSet();


//    std::vector<std::string> outList = testDataSet.getHeader();
//    int k = testList.size();
//    for (int i = 0; i < k; ++i)
//    {
//        ASSERT_EQ(testList[i], outList[i]);
//    }

}

TEST_F(DataSetTest, InitializeDataSet)
{
//     C++11 version
//     std::vector<std::string> testList = {"ID=1, ... }
    std::string testFile = "test_file.txt";
    std::string testHead = "ID=1, Molecule, Solubility=2, Molecular Weight=2";
    std::string line1 = "1, Paracetamol, 4.97, 151";
    std::string line2 = "2, Caffeine, 5.05, 194";
    std::string line3 = "3, Indomethacin, 0.4, 358";
    std::string line4 = "4,Trimethoprim, 3.14, 290";

    std::ofstream testFileStream(testFile.c_str());
    if (!testFileStream) {
        FAIL();
    }
    testFileStream << testHead << std::endl;
    testFileStream << line1 << std::endl;
    testFileStream << line2 << std::endl;
    testFileStream << line3 << std::endl;
    testFileStream << line4 << std::endl;
    testFileStream.close();

    DataSet testDataSet = DataSet(testFile,",");

    std::vector<std::string> testOutHeader = testDataSet.getHeader();
    testDataSet.displaySet(std::cout,",");
    std::vector<std::string> row1 = testDataSet.getRow();

    int returnCode = std::remove(testFile.c_str());
    if (returnCode != 0) {
        FAIL();
    }
}
