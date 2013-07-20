#ifndef BASE_ITEM_H
#define BASE_ITEM_H

#include <string>
#include <vector>
#include <ostream>
#include <cassert>
#include <sstream>

namespace mos {

class Item
{
public:
    virtual ~Item();
    unsigned int type;
    virtual unsigned int size() = 0;
    virtual std::string getRepr(unsigned int index) = 0;
    //virtual std::string getDatum(unsigned int index,
    //                             const std::vector<std::string>& inData) = 0;
    virtual int getIntDatum(unsigned int index);
    //virtual double getDoubleDatum(unsigned int index) = 0;
    enum typeId {
        STRING = 0, INT = 1, DOUBLE = 2
    };
};

template <typename T>
class Column : public Item
{
public:
    std::vector<T> data;
    T getDatum(unsigned int index);
    void push_back(T value);
    unsigned int size();
    std::string getRepr(unsigned int index);

private:
    enum typeId {
        STRING = 0, INT = 1, DOUBLE = 2
    };
    std::string stringBuffer;
    int intBuffer;
    double doubleBuffer;
};



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

//class StringColumn : public Item
//{
//public:
//    std::vector<std::string> column;

//};

//class IntColumn : public Item
//{
//public:
//    std::vector<int> column;
//};

//class DoubleColumn : public Item
//{
//public:
//    std::vector<double> column;
//};

}   // namespace

#endif  // BASE_ITEM_H
