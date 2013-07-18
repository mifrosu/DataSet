#include "data_set.h"
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


void split(const std::string& inString, std::vector<std::string>* store,
           const char* delimiter)
{
    if (inString.size() == 0) {
        return;
    }

    std::string::size_type i = 0;
    std::string::size_type j = inString.find(delimiter);

    if (j== std::string::npos)  // no delimiter found
    {
        store->push_back(inString);
    }

    while (j != std::string::npos) {
        std::string temp = inString.substr(i, j-i);
        strip(&temp);
        store->push_back(temp);
        i = ++j;
        j = inString.find(delimiter, j);

        if (j == std::string::npos) {
            temp = inString.substr(i, inString.length());
            strip(&temp);
            store->push_back(temp);
        }
    }
}

void stripEnd(std::string* inString)
{
    if (inString->empty()) {
        return;
    }

    std::string::iterator iter = inString->end()-1; // move iter to last char

    while (iter != inString->begin() && isspace(*iter)) {
        --iter;
    }

    if (!isspace(*iter) && iter != inString->end()) {
        ++iter;
    }

    if (isspace(*iter) && iter != inString->end()) {
        inString->erase(iter, inString->end());
    }
}

void stripBegin(std::string* inString)
{
    if (inString->empty()) {
        return;
    }

    std::string::iterator iter = inString->begin();
    while (iter != inString->end() && isspace(*iter)) {
        ++iter;
    }

    if (!isspace(*iter) && iter != inString->begin()) {
        --iter;
    }

    if (isspace(*iter)) {
        inString->erase(inString->begin(), iter+1);
    }
}

void strip(std::string* inString)
{
    if (inString->empty())
        return;

    // trim end
    stripEnd(inString);
    stripBegin(inString);
}



}
