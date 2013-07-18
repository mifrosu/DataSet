#include "data_set.h"
#include "string_clean.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

namespace mos {

DataSet::DataSet(const std::string& fileName, const char* delimiter)
{
    std::ifstream inFileStream(fileName.c_str());
    if (!inFileStream) {
        std::cerr << fileName << " can not be accessed." << std::endl;
    }
    else {
        headerList.push_back("UNIQUE_KEY=1");
        std::string inHeader;
        getline(inFileStream, inHeader);
        split(inHeader, &headerList, delimiter);
        processHeader();
    }

}

std::vector<std::string> DataSet::getHeader() const
{
    return headerList;
}

std::vector<std::string> DataSet::getRow() const
{
    std::vector<std::string> thisRow;
    return thisRow;

}

void DataSet::addRow(const std::string &lineIn)
{
    // You are here!
    // need convert string -> int, double
    // what to place if data is missing or wrong?
    // NaN for numbers, blank for strings?

}

void DataSet::displaySet(std::ostream &os, const char* delimiter)
{
    if (headerList.size() >= 1) {
        std::vector<std::string>::const_iterator iter;
        for (iter = headerList.begin(); iter != headerList.end();
             ++iter) {
            os << *iter << delimiter;
        }
        os << std::endl;
    }

    if (dataSet.size() >= 1) {
        unsigned int rowLength = dataSet.size();
        if (dataSet[0]->size() > 0) {
            unsigned int columnDepth = dataSet[0]->size();
            for (unsigned int c = 0; c != columnDepth; ++c) {
                for (unsigned int r = 0; r != rowLength; ++r) {
                    os << dataSet[0]->getRepr(r) << delimiter;
                }
            }
        }
        os << std::endl;
    }
}

void DataSet::addColumn(const unsigned int type)
{
    switch (type) {
    case INT:
        dataSet.push_back(std::make_shared<IntColumn>());
        break;
    case DOUBLE:
        dataSet.push_back(std::make_shared<DoubleColumn>());
        break;
    default:
        dataSet.push_back(std::make_shared<StringColumn>());
        break;
    }
}

void DataSet::processHeader()
{
    if (headerList.size() > 0) {
        std::vector<std::string>::const_iterator iter;
        std::vector<std::string>::const_iterator iterEnd = headerList.end();
        for (iter = headerList.begin(); iter != iterEnd; ++iter) {
            assert((*iter).size() > 2);
            unsigned int k = iter->size();
            if ((*iter)[k-2] == '=') {
                std::stringstream inValue;
                inValue << (*iter)[k-1];
                unsigned int typeId;
                inValue >> typeId;
                if (typeId <= 2) {
                    addColumn(typeId);
                }
            }
            else {
                addColumn(STRING);
            }
            std::cout << (*iter)[k-2];
            std::cout << std::endl;
        }
    }
}



}
