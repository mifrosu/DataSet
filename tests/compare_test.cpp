#include "../data_set.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <iostream>

using namespace mos;

class CompareTest : public ::testing::Test
{
public:
    CompareTest()
    {}

    virtual void SetUp()
    {
        std::string header1 = "number=1, name, letter";
        std::string tla0 = "0, zero, A";
        std::string tla1 = "1, one, B";
        std::string tla2 = "2, two, C";
        std::string tla3 = "3, three, D";

        std::ofstream testFileStream1(fileName1.c_str());
        if (!testFileStream1) {
            std::cout << "Error creating " << fileName1 << std::endl;
        }
        else {
            testFileStream1 << header1 << std::endl;
            testFileStream1 << tla0 << std::endl;
            testFileStream1 << tla1 << std::endl;
            testFileStream1 << tla2 << std::endl;
            testFileStream1 << tla3 << std::endl;
            testFileStream1.close();
        }

        std::string header2 = "letter, number=1, name";
        std::string tlb0 = "G, 6, six";
        std::string tlb1 = "H, 7, Seven";
        std::string tlb4 = "I, 9, nine";
        std::string tlb5 = "F, 5, five";

    std::ofstream testFileStream2(fileName2.c_str());
        if (!testFileStream2) {
            std::cout << "Error creating " << fileName2 << std::endl;
        }
        else {
            testFileStream2 << header2 << std::endl;
            testFileStream2 << tlb0 << std::endl;
            testFileStream2 << tlb1 << std::endl;
            testFileStream2 << tlb4 << std::endl;
            testFileStream2 << tlb5 << std::endl;
            testFileStream2.close();
        }

        std::string header3 = "letterName, number=1, letter";
        std::string tlc0 = "Golf, 6, G";
        std::string tlc1 = "Hotel, 7, H";
        std::string tlc2 = "Charlie, 2, C";
        std::string tlc3 = "Delta, 3, D";
        std::string tlc5 = "Foxtrot, , F";

    std::ofstream testFileStream3(fileName3.c_str());
        if (!testFileStream3) {
            std::cout << "Error creating " << fileName3 << std::endl;
        }
        else {
            testFileStream3 << header3 << std::endl;
            testFileStream3 << tlc0 << std::endl;
            testFileStream3 << tlc1 << std::endl;
            testFileStream3 << tlc2 << std::endl;
            testFileStream3 << tlc3 << std::endl;
            testFileStream3 << tlc5 << std::endl;
            testFileStream3.close();
        }
    }

    virtual void TearDown()
    {
        int returnCode = std::remove(fileName1.c_str());
        if (returnCode != 0) {
            std::cout << "There was a problem deleting "
                      << fileName1 << std::endl;
        }

        returnCode = std::remove(fileName2.c_str());
        if (returnCode != 0) {
            std::cout << "There was a pronumberblem deleting "
                      << fileName2 << std::endl;
        }

        returnCode = std::remove(fileName3.c_str());
        if (returnCode != 0) {
            std::cout << "There was a problem deleting "
                      << fileName3 << std::endl;
        }

    }

    std::string fileName1 = "fileName1.txt";
    std::string fileName2 = "fileName2.txt";
    std::string fileName3 = "fileName3.txt";

};


TEST_F(CompareTest, SimpleMergeTest)
{
    DataSet dataSet1 = DataSet("fileName1.txt", ",");
    DataSet dataSet2 = DataSet("fileName2.txt", ",");

    DataSet outData = dataSet1.merge(dataSet2, "name");
    std::vector<std::string> row0 = outData.getRow(0);
    unsigned int size = outData.getSize();
    std::vector<std::string> rowLast = outData.getRow(size-1);
    std::vector<std::string> expectRow0 = {"0", "0", "zero", "A"};
    std::vector<std::string> expectRowLast = {"7","5", "five", "F"};
    ASSERT_EQ(expectRow0, row0);
    ASSERT_EQ(expectRowLast, rowLast);
}

TEST_F(CompareTest, MismatchedMergeTest)
{
    DataSet dataSet2 = DataSet("fileName2.txt", ",");
    DataSet dataSet3 = DataSet("fileName3.txt", ",");
    DataSet outData = dataSet2.merge(dataSet3,"number=1");
    outData.displaySet(std::cout);
    std::vector<std::string> outHeader = outData.getHeader();
    std::vector<std::string> expectedHeader =
         { "UNIQUE_KEY=1", "letter", "number=1", "name", "letterName" };
    std::vector<std::string> row0 = outData.getRow(0);
    std::vector<std::string> rowLast = outData.getRow(outData.getSize()-1);
    std::vector<std::string> expectedRow0 = { "0", "G", "6", "six", "Golf" };
    std::vector<std::string> expectedRowLast =
       { "6", "F", "-1", " ", "Foxtrot" };
    ASSERT_EQ(expectedHeader, outHeader);
    ASSERT_EQ(expectedRow0, row0);
    ASSERT_EQ(expectedRowLast, rowLast);
}

TEST_F(CompareTest, UnionTest)
{
    DataSet dataSet2 = DataSet("fileName2.txt", ",");
    DataSet dataSet3 = DataSet("fileName3.txt", ",");
    DataSet outData = dataSet2.unionSet(dataSet3,"number=1");
    outData.displaySet(std::cout);
//    std::vector<std::string> outHeader = outData.getHeader();
//    std::vector<std::string> expectedHeader =
//         { "UNIQUE_KEY=1", "letter", "number=1", "name", "letterName" };
//    std::vector<std::string> row0 = outData.getRow(0);
//    std::vector<std::string> rowLast = outData.getRow(outData.getSize()-1);
//    std::vector<std::string> expectedRow0 = { "0", "G", "6", "six", "Golf" };
//    std::vector<std::string> expectedRowLast =
//       { "6", "F", "-1", " ", "Foxtrot" };
//    ASSERT_EQ(expectedHeader, outHeader);
//    ASSERT_EQ(expectedRow0, row0);
//    ASSERT_EQ(expectedRowLast, rowLast);
}

TEST_F(CompareTest, DifferenceTest)
{
    DataSet dataSet2 = DataSet("fileName2.txt", ",");
    DataSet dataSet3 = DataSet("fileName3.txt", ",");
    DataSet outData = dataSet2.differenceSet(dataSet3,"number=1");
    outData.displaySet(std::cout);
//    std::vector<std::string> outHeader = outData.getHeader();
//    std::vector<std::string> expectedHeader =
//         { "UNIQUE_KEY=1", "letter", "number=1", "name", "letterName" };
//    std::vector<std::string> row0 = outData.getRow(0);
//    std::vector<std::string> rowLast = outData.getRow(outData.getSize()-1);
//    std::vector<std::string> expectedRow0 = { "0", "G", "6", "six", "Golf" };
//    std::vector<std::string> expectedRowLast =
//       { "6", "F", "-1", " ", "Foxtrot" };
//    ASSERT_EQ(expectedHeader, outHeader);
//    ASSERT_EQ(expectedRow0, row0);
//    ASSERT_EQ(expectedRowLast, rowLast);
}

TEST_F(CompareTest, IntersectionTest)
{
    DataSet dataSet2 = DataSet("fileName2.txt", ",");
    DataSet dataSet3 = DataSet("fileName3.txt", ",");
    DataSet outData = dataSet2.intersectionSet(dataSet3,"number=1");
    outData.displaySet(std::cout);
//    std::vector<std::string> outHeader = outData.getHeader();
//    std::vector<std::string> expectedHeader =
//         { "UNIQUE_KEY=1", "letter", "number=1", "name", "letterName" };
//    std::vector<std::string> row0 = outData.getRow(0);
//    std::vector<std::string> rowLast = outData.getRow(outData.getSize()-1);
//    std::vector<std::string> expectedRow0 = { "0", "G", "6", "six", "Golf" };
//    std::vector<std::string> expectedRowLast =
//       { "6", "F", "-1", " ", "Foxtrot" };
//    ASSERT_EQ(expectedHeader, outHeader);
//    ASSERT_EQ(expectedRow0, row0);
//    ASSERT_EQ(expectedRowLast, rowLast);
}




