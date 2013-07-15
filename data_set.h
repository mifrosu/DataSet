#ifndef DATA_SET_H
#define DATA_SET_H

#include "item.h"
#include <memory>
#include <string>
#include <vector>

namespace mos_dataset
{

class DataSet
{

public:
    DataSet(const std::vector<std::string> headerList);

    std::vector<std::string> getHeader() const;

private:

    enum column_type
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
    typedef std::vector<std::shared_ptr<Item> > itemVector;

    /**
     * @brief dataSet
     * dataSet represents the table data.
     */
    std::vector<itemVector> dataSet;
};





}   // namespace

#endif  // DATA_SET_H

