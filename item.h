#ifndef BASE_ITEM_H
#define BASE_ITEM_H

#include <string>
#include <vector>
#include <ostream>

namespace mos {

struct Item
{
    virtual ~Item();
    unsigned type;
};

template <typename T>
struct Column : public Item
{
    std::vector<T> data;
};


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
