#include "data_set.h"
#include "string_clean.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <boost/lexical_cast.hpp>

namespace mos {

DataSet::DataSet() : rowCount(0)
{

}

void DataSet::addFile(const std::string &fileName, const char *delimiter)
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

DataSet::DataSet(const std::string& fileName, const char* delimiter)
{
    clearSet();
    addFile(fileName, delimiter);
}

void DataSet::clearSet()
{
    rowCount = 0;
    headerList.clear();
    dataSet.clear();
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
                os << std::endl;
            }
        }
        os << std::endl;
    }
}

void DataSet::addCell(int cellItem, itemVectorPtr column)
{
    if (column->type == INT) {
        column->push_back(cellItem);
    }
    return;
}

void DataSet::addCell(double cellItem, itemVectorPtr column)
{
    if (column->type == DOUBLE) {
        column->push_back(cellItem);
    }
    return;
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

unsigned int DataSet::findHeader(const std::string &header)
{
    std::vector<std::string>::iterator iter = headerList.begin();
    std::vector<std::string>::iterator iterEnd = headerList.end();

    iter = std::find(iter, iterEnd, header);
    if (iter == iterEnd) {
        // not found
        return -1;
    }
    else {
        return std::distance(headerList.begin(),iter);
    }
}

//void DataSet::findUnique(std::vector<char> *store,
//                         unsigned int rowIndex)
//{
//    store->clear();
//    unsigned int columnDepth = dataSet[0]->size();
//    if (columnDepth == 0) {
//        return;
//    }
//    for (unsigned int k = 0; k != columnDepth; ++k)
//    {
//        store->push_back('y');
//    }
//    switch (dataSet[rowIndex]->type) {
//    case DOUBLE:


//        break;
//    default:
//        break;
//    }

//}

std::vector<unsigned int> DataSet::getOtherHeaderIndices(
        const DataSet& other) {

    std::vector<unsigned int> indexList;
    unsigned int otherEnd = other.headerList.size();
    if (otherEnd == 0) {
        return indexList;
    }
    std::vector<std::string>::const_iterator iter;
    std::vector<std::string>::const_iterator endIter = headerList.end();

    for (unsigned int i = 0; i != otherEnd; ++i) {
        iter = headerList.begin();
        std::find(iter, endIter,other.headerList[i]);
        if (iter == endIter) {
            // not found
            indexList.push_back(i);
        }
    }
    return indexList;
}

std::vector<unsigned int> DataSet::generateRowPlan(const DataSet &other)
{
    unsigned int columnDepth = other.dataSet[0]->size();
    std::vector<unsigned int> rowPlan;
    if (columnDepth == 0) {
        return rowPlan;
    }
    else {
        for (unsigned int i = 0; i != columnDepth; ++i) {
            rowPlan.push_back(1);
        }
    }
    return rowPlan;
}

void DataSet::setRowPlan(const std::vector<unsigned int> &indexList,
                         std::vector<unsigned int>* rowPlan)
{
    if (rowPlan->size() != indexList.size()) {
        return;
    }
    else {
        std::vector<unsigned int>::const_iterator iter;
        std::vector<unsigned int>::const_iterator endIter = indexList.end();

        for (iter = indexList.begin(); iter != endIter; ++iter)
        {
            (*rowPlan)[*iter] = 0;
        }
    }
    return;
}

std::map<unsigned int, std::vector<unsigned int> > DataSet::match(
        DataSet &other, const std::string& columnName, bool onlyUnique)
{
    std::map<unsigned int, std::vector<unsigned int> > mapBuffer;
    unsigned int thisRowIndex = findHeader(columnName);
    unsigned int otherRowIndex = other.findHeader(columnName);
    // book keeping -- record for rows notmatched
    std::vector<unsigned int> rowPlan = generateRowPlan(other);

    // check for duplicates
    std::vector<char> uniquePlan;
    if (onlyUnique) {
        uniquePlan = dataSet[thisRowIndex]->getUniquePlan();
    }
    if (thisRowIndex == unsigned(-1) ||
            otherRowIndex == unsigned(-1)) {
        std::cerr << "Error: " << columnName
                  << " is not present in both sets." << std::endl;
        return mapBuffer;
    }
    else if (dataSet[thisRowIndex]->type !=
             other.dataSet[otherRowIndex]->type) {
        std::cerr << "Error: Column type mismatch." << std::endl;
    }
    else {
        unsigned int thisColSize = dataSet[thisRowIndex]->size();
        //unsigned int otherColSize = other.dataSet[otherRowIndex]->size();
        for (unsigned int thisX = 0; thisX != thisColSize; ++thisX)
        {
            if (onlyUnique == true && thisX < uniquePlan.size() &&
                    uniquePlan[thisX] == 'n') {
                continue;
            }
            switch (dataSet[thisRowIndex]->type) {

            case INT: {  // note, we need brackets if variables are
                         // initialized within the switch statement
                std::vector<unsigned int> intIndexList;
                int intValue = dataSet[thisRowIndex]->getIntDatum(thisX);
                intIndexList =
                        other.dataSet[otherRowIndex]->findValue(intValue);
                // use thisUNIQUE_KEY column as map key
                mapBuffer[dataSet[0]->getIntDatum(thisX)] = intIndexList;
                setRowPlan(intIndexList, &rowPlan);
                break;
            }
            case DOUBLE: {
                std::vector<unsigned int> dblIndexList;
                double dblValue = dataSet[thisRowIndex]->getDoubleDatum(thisX);
                dblIndexList =
                        other.dataSet[otherRowIndex]->findValue(dblValue);
                // use thisUNIQUE_KEY column as map key
                mapBuffer[dataSet[0]->getIntDatum(thisX)] = dblIndexList;
                setRowPlan(dblIndexList, &rowPlan);
                break;
            }
            default: { //STRING
                std::vector<unsigned int> stringIndexList;
                std::string stringValue =
                        dataSet[thisRowIndex]->getStringDatum(thisX);
                stringIndexList =
                        other.dataSet[otherRowIndex]->findValue(stringValue);
                // use thisUNIQUE_KEY column as map key
                mapBuffer[dataSet[0]->getIntDatum(thisX)] = stringIndexList;
                setRowPlan(stringIndexList, &rowPlan);
                break;
            }
            }
        }
    }
    mapBuffer[unsigned(-1)] = rowPlan;
    return mapBuffer;
}




}
