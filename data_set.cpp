#include "data_set.h"
#include "string_clean.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <boost/lexical_cast.hpp>

namespace mos {

DataSet::DataSet(const std::string& fileName, const char* delimiter) :
    rowCount(0)
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
        std::string line;
        while (inFileStream.good())
        {
            getline(inFileStream, line);
            addRow(line, delimiter);
        }
    }
    inFileStream.close();
}

std::vector<std::string> DataSet::getHeader() const
{
    return headerList;
}

std::vector<std::string> DataSet::getRow(const unsigned int index) const
{
    std::vector<std::string> thisRow;
    if (index < dataSet[0]->size() || index == 0) {
        unsigned int end = headerList.size();
        for (unsigned int  i = 0; i != end; ++i)
        {
            if (index < dataSet[i]->size())
            {
                thisRow.push_back(dataSet[i]->getRepr(index));
            }
            else {
                thisRow.push_back(" ");
            }
        }
    }
    return thisRow;

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
                    os << dataSet[r]->getRepr(c) << delimiter;
                }
            }
        }
        os << std::endl;
    }
}

void DataSet::addCell(const std::string &cellItem, itemVectorPtr column)
{
    if (cellItem == " ") {
        switch (column->type) {
        case INT:
            column->push_back(-1);
            break;
        case DOUBLE:
            column->push_back(std::numeric_limits<double>::quiet_NaN());
            break;
        default: // STRING
            column->push_back(" ");
            break;
        }
    }
    else {
        switch (column->type) {
        case INT:
            try {
                int value = boost::lexical_cast<int>(
                            cellItem);
                column->push_back(value);
            }
            catch (boost::bad_lexical_cast& e) {
                std::cerr << "Problem cast: " << e.what() << std::endl;
            }
            break;
        case DOUBLE:
            try {
                double value = boost::lexical_cast<double>(
                            cellItem);
                column->push_back(value);
            }
            catch (boost::bad_lexical_cast& e) {
                std::cerr << "Problem cast: " << e.what() << std::endl;
            }
            break;
        default: // STRING
            column->push_back(cellItem);
            break;
        }
    }
}

void DataSet::addRow(const std::string &lineIn, const char* delimiter)
{
    std::vector<std::string> lineVector;
    split(lineIn, &lineVector, delimiter);
    if (lineVector.size() > 0) {
        unsigned int dataSetEnd = dataSet.size();
        dataSet[0]->push_back(rowCount);
        std::vector<std::string>::const_iterator iter = lineVector.begin();
        std::vector<std::string>::const_iterator iterEnd = lineVector.end();
        for (unsigned int i = 1; i != dataSetEnd; ++i)
        {
            if (iter < iterEnd) {
                addCell(*iter, dataSet[i]);
                ++iter;
            }
            else {
                addCell(" ", dataSet[i]);
            }

        }
        ++rowCount;

    }
    else {
        return;
    }

    // You are here!
    // need convert string -> int, double
    // what to place if data is missing or wrong?
    // NaN for numbers, blank for strings?

}

void DataSet::setColumnType(const unsigned int columnType)
{
    unsigned int currentIndex = dataSet.size()-1;
    switch (columnType) {
    case STRING:
        dataSet[currentIndex]->type = STRING;
        break;
    case INT:
        dataSet[currentIndex]->type = INT;
        break;
    case DOUBLE:
        dataSet[currentIndex]->type = DOUBLE;
        break;
    }
}


void DataSet::addColumn(const unsigned int columnType)
{
    switch (columnType) {
    case INT:
        dataSet.push_back(std::make_shared<IntColumn>());
        setColumnType(INT);
        break;
    case DOUBLE:
        dataSet.push_back(std::make_shared<DoubleColumn>());
        setColumnType(DOUBLE);
        break;
    default:
        dataSet.push_back(std::make_shared<StringColumn>());
        setColumnType(STRING);
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
                unsigned int typeId = 0;
                try {
                    typeId = boost::lexical_cast<unsigned int>(
                                (*iter)[k-1]);
                }
                catch (boost::bad_lexical_cast& e) {
                    std::cerr << "Problem cast: " << e.what() << std::endl;
                }
                if (typeId <= 2) {
                    // typeId will be 0 (STRING) if lexical_cast fails
                    addColumn(typeId);
                }
            }
            else {
                addColumn(STRING);
            }
        }
    }
}



}
