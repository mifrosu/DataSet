#ifndef BASE_ITEM_H
#define BASE_ITEM_H

#include <string>
#include <vector>
#include <ostream>
#include <cassert>

namespace mos {

class Item
{
public:
    virtual ~Item();
    unsigned int type;
};

template <typename T>
class Column : public Item
{
public:
    std::vector<T> data;
    T getDatum(unsigned int index);
    void push_back(T value);

};

template <typename T>
T Column<T>::getDatum(unsigned int index)
{
    assert(index < data.size());
    if (index < data.size()) {
        return data[index];
    }
}

template <typename T>
void Column<T>::push_back(T value)
{
    data.push_back(value);
}

typedef Column<std::string> StringColumn;
typedef Column<int> IntColumn;
typedef Column<double> DoubleColumn;


//class Item
//{
//public:

//    virtual ~Item();
//    int type;
//    int currentIndex;
//    int futureIndex;

//private:
//    Item();
//};

//class StringItem : public Item
//{
//public:
//    StringItem();
//    std::vector<std::string> column;

//};

//class IntItem : public Item
//{
//public:
//    IntItem();
//    std::vector<int> column;
//};

//class DoubleItem : public Item
//{
//public:
//    DoubleItem();
//    std::vector<double> column;
//};

}   // namespace

#endif  // BASE_ITEM_H
