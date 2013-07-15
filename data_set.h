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
    DataSet(std::vector<std::string> headerList);

private:

    enum column_type
    {
        STRING = 0, INT = 1, DOUBLE = 2
    };

    std::vector<std::string> headerList;
    typedef std::vector<std::shared_ptr<Item> > itemVector;
    std::vector<itemVector> dataSet;
};





}   // namespace

#endif  // DATA_SET_H

