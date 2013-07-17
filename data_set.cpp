#include "data_set.h"
#include <fstream>
#include <iostream>

namespace mos {

DataSet::DataSet(const std::string& fileName, const char* delimiter)
{
    std::ifstream inFileStream(fileName.c_str());
    if (!inFileStream) {
        std::cerr << fileName << " can not be accessed." << std::endl;
    }
    std::string inHeader;
    getline(inFileStream, inHeader);
    split(inHeader, &headerList, delimiter);
    processHeader();
}

std::vector<std::string> DataSet::getHeader() const
{
    return headerList;
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

//    if (dataSet.size() >= 1) {
//        int rowLength = dataSet.size();
//        if (dataSet[0]->size() > 0) {
//            int columnDepth = dataSet[0]->size();
//            for (unsigned int c = 0; c != columnDepth; ++c) {
//                for (unsigned int r = 0; r != rowLength; ++r) {
//                    os << dataSet[c][r] << delimiter;
//                }
//            }
//        }
//        os << std::endl;
//    }
}

void DataSet::processHeader()
{
    if (headerList.size() > 0) {
        std::vector<std::string>::const_iterator iter;
        std::vector<std::string>::const_iterator iterEnd = headerList.end();
        for (iter = headerList.begin(); iter != iterEnd; ++iter) {
            if ((*iter).size() > 2) {
                int k = iter->size();
                if ((*iter)[k-2] == '=') {
                    std::cout << (*iter)[k-1];
                }
                std::cout << (*iter)[k-2];
            }
            std::cout << std::endl;
        }
    }
}

void DataSet::insertColumn(int columnType)
{
    switch (columnType) {
    default:

//        std::shared_ptr<Item> cell(new StringItem);
//        std::shared_ptr<std::vector<std::shared_ptr<Item> column(
//                    new std::vector<StringItem>);
//        column->push_back(cell);
//        dataSet.push_back(column);
        break;
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
