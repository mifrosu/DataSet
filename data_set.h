#ifndef DATA_SET_H
#define DATA_SET_H

#include "item.h"
#include <memory>       // std::shared_ptr
#include <string>
#include <vector>
#include <ostream>
//#include <functional>
#include <cctype>       // isspace
#include <map>

namespace mos
{

class DataSet
{

public:

    DataSet();
    DataSet(const std::string& fileName, const char* delimiter="\t");

    void addFile(const std::string& fileName, const char* delimiter="\t");
    void clearSet();

    std::vector<std::string> getHeader() const;
    std::vector<std::string> getRow(const unsigned int index) const;

    void displaySet(std::ostream& os, const char* delimiter="\t");

    DataSet merge(const DataSet& other, const std::string& columnName);
    DataSet unionSet(const DataSet& other, const std::string& columnName);
    DataSet differenceSet(const DataSet& other, const std::string& columnName);
    DataSet intersectionSet(const DataSet& other,
                            const std::string& columnName);

private:
    /**
     * @brief itemVectorPtr
     * Each derived Item object will hold a datum, corresponding
     * to a table cell. ItemVectorPtr corresponds to a table column.
     */
    typedef std::shared_ptr<Item> itemVectorPtr;

    void addHeader(const std::string& headerLine);
    void setColumnType(const unsigned int columnType);
    void addCell(const std::string& cellItem, itemVectorPtr column);
    void addRow(const std::string& lineIn, const char* delimiter);
    void addColumn(const unsigned int columnType);
    void processHeader();

    void match(DataSet& other, const std::string& columnName);
    unsigned int findHeader(const std::string& header);

    std::string getDatum(std::shared_ptr<Item> cellPtr,
                         unsigned int index);
    enum columnType
    {
        STRING = 0, INT = 1, DOUBLE = 2
    };

    /**
     * @brief headerList
     * Holds the column IDs
     */
    std::vector<std::string> headerList;



    /**
     * @brief dataSet
     * dataSet represents the table data.
     */
    std::vector<itemVectorPtr> dataSet;

    int rowCount;
    std::map<unsigned int, std::vector<unsigned int> > mapBuffer;
};

// non-member, non-friend functions






}   // namespace

#endif  // DATA_SET_H

