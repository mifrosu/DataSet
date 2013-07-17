#ifndef DATA_SET_H
#define DATA_SET_H

#include "item.h"
#include <memory>
#include <string>
#include <vector>
#include <ostream>
//#include <functional>
#include <cctype>       // isspace

namespace mos
{

class DataSet
{

public:

    DataSet();
    DataSet(const std::string& fileName, const char* delimiter="\t");

    void addFile(const std::string& fileName, const char* delimiter="\t");

    std::vector<std::string> getHeader() const;

    void displaySet(std::ostream& os, const char* delimiter="\t");

private:

    void addHeader(const std::string& headerLine);
    void addRow(const std::string& lineIn);
    void processHeader();
    void insertColumn(int columnType);

    std::string getDatum(std::shared_ptr<Item> cellPtr,
                         unsigned int index);
    enum columnTypeEnums
    {
        STRING = 0, INT = 1, DOUBLE = 2
    };

    /**
     * @brief headerList
     * Holds the column IDs
     */
    std::vector<std::string> headerList;

    /**
     * @brief itemVector
     * Each derived Item object will hold a datum, corresponding
     * to a table cell. ItemVector corresponds to a table column.
     */
    typedef std::shared_ptr<Item> itemVectorPtr;

    /**
     * @brief dataSet
     * dataSet represents the table data.
     */
    std::vector<itemVectorPtr> dataSet;
};

// non-member, non-friend functions

void split(const std::string& inString, std::vector<std::string>* store,
           const char* delimiter="\t");

/// in-place strip terminal whitespace
void strip(std::string* inString);
void stripEnd(std::string* inString);
void stripBegin(std::string* inString);

}   // namespace

#endif  // DATA_SET_H

