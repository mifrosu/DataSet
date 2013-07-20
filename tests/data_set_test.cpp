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
        testFile = "test_file.txt";
        testHead = "ID=1, Molecule, Solubility=2, Molecular Weight=2";
        line1 = "1, Paracetamol, 4.97, 151";
        line2 = "2, Caffeine, 5.05, 194";
        line3 = "3, Indomethacin, 0.4, 358";
        line4 = "4,Trimethoprim, 3.14, 290";

    }

    virtual void TearDown()
    {

    }

    std::string testFile;
    std::string testHead;
    std::string line1;
    std::string line2;
    std::string line3;
    std::string line4;
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
    // std::string testFile = "test_file.txt";
    std::string testHead0 = "ID=1, Molecule, Solubility=2, Molecular Weight=2";

    std::ofstream testFileStream(testFile.c_str());
    if (!testFileStream) {
        FAIL();
    }
    testFileStream << testHead0 << std::endl;
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

TEST_F(DataSetTest, InitializeDataSetEmpty)
{
//     C++11 version
//     std::vector<std::string> testList = {"ID=1, ... }

    std::ofstream testFileStream(testFile.c_str());
    if (!testFileStream) {
        FAIL();
    }
    testFileStream << testHead << std::endl;
    testFileStream.close();

    DataSet testDataSet = DataSet(testFile,",");

    std::vector<std::string> testOutHeader = testDataSet.getHeader();
    testDataSet.displaySet(std::cout,",");
    std::vector<std::string> row1 = testDataSet.getRow(0);
    std::vector<std::string> emptyRow;
    std::vector<std::string>::const_iterator k;
    for (k = testOutHeader.begin(); k != testOutHeader.end(); ++k) {
        emptyRow.push_back(" ");
    }
    ASSERT_EQ(5, emptyRow.size());
    ASSERT_EQ(emptyRow, row1);

    int returnCode = std::remove(testFile.c_str());
    if (returnCode != 0) {
        FAIL();
    }
}

TEST_F(DataSetTest, InitializeDataSetLines)
{

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
    std::vector<std::string> row0 = testDataSet.getRow(0);
    std::vector<std::string> row1 = testDataSet.getRow(1);
    std::vector<std::string> row2 = testDataSet.getRow(2);
    std::vector<std::string> row3 = testDataSet.getRow(3);
    // Note: the following assignments are only valid for C++11
    std::vector<std::string> test0 = {"0","1", "Paracetamol", "4.97", "151"};
    std::vector<std::string> test1 = {"1", "2", "Caffeine", "5.05", "194"};
    std::vector<std::string> test2 = {"2", "3", "Indomethacin", "0.4", "358"};
    std::vector<std::string> test3 = {"3", "4", "Trimethoprim", "3.14", "290"};
    ASSERT_EQ(test0, row0);
    ASSERT_EQ(test1, row1);
    ASSERT_EQ(test2, row2);
    ASSERT_EQ(test3, row3);

    int returnCode = std::remove(testFile.c_str());
    if (returnCode != 0) {
        FAIL();
    }
}
