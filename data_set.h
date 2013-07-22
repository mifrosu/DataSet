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
#include <limits>

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
    unsigned int getSize();

    void displaySet(std::ostream& os, const char* delimiter="\t");

    DataSet merge(const DataSet& other, const std::string& columnName,
                  bool onlyUnique=false);
    DataSet unionSet(const DataSet& other, const std::string& columnName,
                     bool onlyUnique=true);
    DataSet differenceSet(const DataSet& other, const std::string& columnName,
                          bool onlyUnique=true);
    DataSet intersectionSet(const DataSet& other,
                            const std::string& columnName,
                            bool onlyUnique=true);

private:
    /**
     * @brief itemVectorPtr
     * Each derived Item object will hold a datum, corresponding
     * to a table cell. ItemVectorPtr corresponds to a table column.
     */
    typedef std::shared_ptr<Item> itemVectorPtr;

    struct DataBuffer {
        int intBuffer;
        double doubleBuffer;
        std::string stringBuffer;
        int setId;
        DataBuffer()
            : intBuffer(-1),
              doubleBuffer(std::numeric_limits<double>::quiet_NaN()),
              stringBuffer(" "),
              setId(-1) {}
    };

    void addHeader(const std::string& headerLine);
    void setColumnType(const unsigned int columnType);
    void addRow(const std::string& lineIn, const char* delimiter);
    void addCell(int cellItem, itemVectorPtr column);
    void addCell(double cellItem, itemVectorPtr column);
    void addCell(const std::string& cellItem, itemVectorPtr column);

    void getDatum(unsigned int index, itemVectorPtr column,
                  DataBuffer& dataBuffer);
    void addRowItem(itemVectorPtr outColumn,
                             const DataBuffer& outBuffer);

    // other columnIndex is set to -1 if N/A
    void addRow(unsigned int thisColumnIndex,
                const std::vector<unsigned int>& otherHeaderIndex,
                const DataSet& other,
                DataSet& outDataSet,
                unsigned int otherColumnIndex=-1);
    void addOtherRow(unsigned int otherColumnIndex,
                    const std::map<unsigned int, unsigned int>& commonIndexMap,
                    const std::vector<unsigned>& otherHeaderIndexList,
                    const DataSet& other, DataSet& outDataSet);
    void addColumn(const unsigned int columnType);
    void processHeader();
    void generateOutSetHeader(const DataSet& other, DataSet* outDataSet,
            const std::vector<unsigned int>& headerIndices,
            unsigned int* outHeaderMergeIndexStore);

    std::vector<unsigned int> generateMissingIndexList(
            const std::vector<unsigned int>& rowPlan);
    void match(const DataSet& other, const std::string& columnName,
          std::map<unsigned int, std::vector<unsigned int> >& mapBuffer,
          bool onlyUnique=false);

    unsigned int findHeader(const std::string& header) const;

    /// Book-keeping functions:
    /// get indices of columns not present herein
    std::vector<unsigned int> getOtherHeaderIndices(
            const DataSet& other) const;
    std::map<unsigned int, unsigned int> getCommonHeaderIndices(
            const DataSet& other) const;

    /// 0 if row cell value in both sets, else 1
    std::vector<unsigned int> generateRowPlan(const DataSet& other);
    void setRowPlan(const std::vector<unsigned int>& indexList,
                    std::vector<unsigned int>* rowPlan);

    std::string getDatum(std::shared_ptr<Item> cellPtr,
                         unsigned int index);

    DataSet generateSet(const DataSet &other, const std::string &columnName,
            std::map<unsigned int, std::vector<unsigned int> >* matchBuffer,
            bool onlyUnique);

    void addSetColumn(DataSet& outputSet, itemVectorPtr column,
                      std::vector<unsigned int> indexList);

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
};

// non-member, non-friend functions






}   // namespace

#endif  // DATA_SET_H

