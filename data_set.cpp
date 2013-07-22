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

unsigned int DataSet::getSize()
{
    return dataSet[0]->size();
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

void DataSet::getDatum(unsigned int index, itemVectorPtr column,
                       DataBuffer &dataBuffer)
{
    if (column == 0) {
        return;
    }
    switch (column->type) {
    case INT:
        dataBuffer.intBuffer = column->getIntDatum(index);
        dataBuffer.setId = INT;
        break;
    case DOUBLE:
        dataBuffer.doubleBuffer = column->getDoubleDatum(index);
        dataBuffer.setId = DOUBLE;
        break;
    default:
        dataBuffer.stringBuffer = column->getStringDatum(index);
        dataBuffer.setId = STRING;
        break;
    }
}

void DataSet::addRowItem(itemVectorPtr outColumn,
                         const DataBuffer& outBuffer)
{
    if (outColumn == 0) {
        return;
    }
    switch (outColumn->type) {
    case INT:
        outColumn->push_back(outBuffer.intBuffer);
        break;
    case DOUBLE:
        outColumn->push_back(outBuffer.doubleBuffer);
        break;
    default:
        outColumn->push_back(outBuffer.stringBuffer);
        break;
    }

}

void DataSet::addOtherRow(unsigned int otherColumnIndex,
                   const std::map<unsigned int, unsigned int>& commonIndexMap,
                   const std::vector<unsigned>& otherHeaderIndexList,
                   const DataSet& other, DataSet& outDataSet)
{
    unsigned int headerEnd = outDataSet.headerList.size();
    std::map<unsigned int, unsigned int>::const_iterator endCommonMapIter;
    endCommonMapIter = commonIndexMap.end();
    std::map<unsigned int, unsigned int>::const_iterator commonMapIter;

    outDataSet.dataSet[0]->push_back(outDataSet.rowCount);
    for (unsigned int i = 1; i < headerEnd; ++i)
    {

        if (i < headerList.size()) {
            commonMapIter = commonIndexMap.find(i);
            if (commonMapIter != endCommonMapIter) {
                // it is a common index
                DataBuffer dataBuffer;
                unsigned int otherIndex = commonMapIter->second;
                getDatum(otherColumnIndex, other.dataSet[otherIndex],
                         dataBuffer);
                addRowItem(outDataSet.dataSet[i], dataBuffer);
            }
            else {
                // header not in other
                DataBuffer dataBuffer;
                addRowItem(outDataSet.dataSet[i], dataBuffer); // add blank
            }
        }
        else { // now using indices from other only
            unsigned int otherEnd = otherHeaderIndexList.size();
            for (unsigned int k = 0; k != otherEnd; ++k )
            {
                DataBuffer dataBuffer;
                getDatum(otherColumnIndex,
                         other.dataSet[otherHeaderIndexList[k]], dataBuffer);
                addRowItem(outDataSet.dataSet[i], dataBuffer);
                ++i;
            }
        }
    }
    ++outDataSet.rowCount;
}

void DataSet::addRow(unsigned int thisColumnIndex,
            const std::vector<unsigned int>& otherHeaderIndex,
            const DataSet& other,
            DataSet& outDataSet,
            unsigned int otherColumnIndex)
{
    unsigned int outHeaderListSize = outDataSet.headerList.size();
    // set the unique value
    outDataSet.dataSet[0]->push_back(outDataSet.rowCount);
    for (unsigned int i = 1; i < outHeaderListSize; ++i) {
        if ( i >= headerList.size()) {
            for (unsigned int k = 0; k != otherHeaderIndex.size(); ++k) {
                // we now bring in data from other
                DataBuffer outBuffer;
                if (otherColumnIndex != unsigned(-1)) {
                    getDatum(otherColumnIndex,
                             other.dataSet[otherHeaderIndex[k]], outBuffer);
                }
                addRowItem(outDataSet.dataSet[i], outBuffer);
                ++i; // increment i for each k added
            }
        }
        else {
            DataBuffer outBuffer;
            getDatum(thisColumnIndex, dataSet[i], outBuffer);
            addRowItem(outDataSet.dataSet[i], outBuffer);
        }

    }
    ++outDataSet.rowCount;
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

unsigned int DataSet::findHeader(const std::string &header) const
{
    std::vector<std::string>::const_iterator iter = headerList.begin();
    std::vector<std::string>::const_iterator iterEnd = headerList.end();

    iter = std::find(iter, iterEnd, header);
    if (iter == iterEnd) {
        // not found
        return -1;
    }
    else {
        std::vector<std::string>::const_iterator start = headerList.begin();
        return std::distance(start,iter);
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
        const DataSet& other) const
{

    std::vector<unsigned int> indexList;
    unsigned int otherEnd = other.headerList.size();
    if (otherEnd == 0) {
        return indexList;
    }
    std::vector<std::string>::const_iterator iter;
    std::vector<std::string>::const_iterator endIter = headerList.end();

    for (unsigned int i = 0; i != otherEnd; ++i) {
        iter = headerList.begin();
        iter = std::find(iter, endIter,other.headerList[i]);
        if (iter == endIter) {
            // not found
            indexList.push_back(i);
        }
    }
    return indexList;
}

std::map<unsigned int, unsigned int> DataSet::getCommonHeaderIndices(
        const DataSet &other) const
{
    // to find the indices of headers common to the two datasets
    // the key is set to this header's index, while the value is
    // that of the other
    std::map<unsigned int, unsigned int> indexMap;
    if (other.headerList.size() == 0) {
        return indexMap; // nothing to do
    }

    unsigned int thisEnd = headerList.size();
    unsigned int otherEnd = other.headerList.size();
    unsigned int thisX;
    unsigned int otherX;

    // we ignore 0 index (UNIQUE_KEY) in both cases
    for (thisX = 1; thisX != thisEnd; ++thisX ) {
        for (otherX = 1; otherX != otherEnd; ++otherX) {
            if (headerList[thisX] == other.headerList[otherX]) {
                indexMap[thisX] = otherX;
                continue;
            }
        }
    }
    return indexMap;
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
    // values will remain 1 if no corresponding value in indexList
    // which means those rows have no matches with this

    std::vector<unsigned int>::const_iterator iter;
    std::vector<unsigned int>::const_iterator endIter = indexList.end();

    for (iter = indexList.begin(); iter != endIter; ++iter)
    {
        (*rowPlan)[*iter] = 0;
    }

    return;
}

std::vector<unsigned int> DataSet::generateMissingIndexList(
        const std::vector<unsigned int>& rowPlan)
{
    std::vector<unsigned int> missingIndexList;
    unsigned int end = rowPlan.size();
    if (end == 0) {
        return missingIndexList;
    }
    for (unsigned int i = 0; i != end; ++i) {
        if (rowPlan[i] == 1) {
            missingIndexList.push_back(i);
        }
    }
    return missingIndexList;
}

void DataSet::match(
        const DataSet& other, const std::string& columnName,
        std::map<unsigned int, std::vector<unsigned int> >& mapBuffer,
        bool onlyUnique)
{
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
        return;
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
                setRowPlan(intIndexList, &rowPlan);
                if (onlyUnique && intIndexList.size() > 1) {
                    // remove unneeded elements
                    intIndexList.erase(intIndexList.begin()+1,
                                       intIndexList.end());
                }
                mapBuffer[dataSet[0]->getIntDatum(thisX)] = intIndexList;

                break;
            }
            case DOUBLE: {
                std::vector<unsigned int> dblIndexList;
                double dblValue = dataSet[thisRowIndex]->getDoubleDatum(thisX);
                dblIndexList =
                        other.dataSet[otherRowIndex]->findValue(dblValue);
                // use thisUNIQUE_KEY column as map key
                setRowPlan(dblIndexList, &rowPlan);
                if (onlyUnique && dblIndexList.size() > 1) {
                    dblIndexList.erase(dblIndexList.begin()+1,
                                       dblIndexList.end());
                }
                mapBuffer[dataSet[0]->getIntDatum(thisX)] = dblIndexList;

                break;
            }
            default: { //STRING
                std::vector<unsigned int> stringIndexList;
                std::string stringValue =
                        dataSet[thisRowIndex]->getStringDatum(thisX);
                stringIndexList =
                        other.dataSet[otherRowIndex]->findValue(stringValue);
                // use thisUNIQUE_KEY column as map key
                setRowPlan(stringIndexList, &rowPlan);
                if (onlyUnique && stringIndexList.size() > 1) {
                    stringIndexList.erase(stringIndexList.begin()+1,
                                          stringIndexList.end());
                }
                mapBuffer[dataSet[0]->getIntDatum(thisX)] = stringIndexList;

                break;
            }
            }
        }
    }
    if (rowPlan.size() != 0) {
        std::vector<unsigned int> missingIndexList
                = generateMissingIndexList(rowPlan);
        mapBuffer[unsigned(-1)] = missingIndexList;
    }

    return;
}

void DataSet::generateOutSetHeader(const DataSet &other, DataSet* outDataSet,
        const std::vector<unsigned int>& otherHeaderIndices,
                                      unsigned int* outHeaderMergeIndexStore)
{
    // make the new header list
    std::vector<std::string>::const_iterator iter = headerList.begin();
    std::vector<std::string>::const_iterator endIter = headerList.end();
    std::vector<std::string> outHeaderList(iter,endIter);

    *outHeaderMergeIndexStore = outHeaderList.size();

    if (otherHeaderIndices.size() > 0) {
        // include new column names from other
        for (unsigned int i = 0; i != otherHeaderIndices.size(); ++i)
        {
            outHeaderList.push_back(other.headerList[otherHeaderIndices[i]]);
        }
    }

    outDataSet->headerList = outHeaderList;
    outDataSet->processHeader();


    return;

}

DataSet DataSet::merge(const DataSet &other, const std::string &columnName,
                       bool onlyUnique)
{
    // Please note: this function requires modification before it may be used
    // to merge data on a column that comprises non-unique values
    std::map<unsigned int, std::vector<unsigned int> >  mapBuffer;

    // we populate the map with unique_key id ints from this
    // and a corresponding vector that contains the matches from other.
    // stored at key unsigned(-1) is a list of indices corresponding to
    // any rows that have no matches for this
    match(other, columnName, mapBuffer, onlyUnique);

    // next we find headList indices from other that do not feature in this
    std::vector<unsigned int> otherHeaders = getOtherHeaderIndices(other);


    // we can now generate our header (keeping note of the merge index with
    // new headers)
    unsigned int mergeIndex = 0;
    DataSet outDataSet;
    generateOutSetHeader(other, &outDataSet, otherHeaders, &mergeIndex);


    // we generate an index map for headers common to both this and other
    std::map<unsigned int, unsigned int> commonIndexMap =
            getCommonHeaderIndices(other);

    // we iterate over mapBuffer to get the column index, and corresponding
    // index for other
    std::map<unsigned int,
            std::vector<unsigned int> >::const_iterator matchMapIter;
    std::map<unsigned int,
            std::vector<unsigned int> >::const_iterator endMatchMapIter =
            mapBuffer.end();

    for (matchMapIter = mapBuffer.begin(); matchMapIter != endMatchMapIter;
         ++matchMapIter)
    {
        if (matchMapIter->first == unsigned(-1)) {

            // this corresponds to the list of other unmatched rows
            std::vector<unsigned int> missingRowIndices = matchMapIter->second;
            std::vector<unsigned int>::iterator missingIter;
            std::vector<unsigned int>::iterator endMissingIter =
                    missingRowIndices.end();
            for (missingIter = missingRowIndices.begin();
                 missingIter != endMissingIter; ++missingIter) {
                addOtherRow(*missingIter, commonIndexMap, otherHeaders,
                            other, outDataSet);
            }
        }
        else if (matchMapIter->second.size() == 0)
        {

            // no other rows match with this row
            addRow(matchMapIter->first, otherHeaders, other, outDataSet);
        }
        else {
            // we have matches with other


            addRow(matchMapIter->first, otherHeaders, other, outDataSet,
                   matchMapIter->second[0]);

        }
    }


    return outDataSet;

}




}
