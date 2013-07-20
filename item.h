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
    virtual std::string getStringDatum(unsigned int index);
    virtual double getDoubleDatum(unsigned int index);
    virtual void push_back (std::string value) {}
    virtual void push_back (int value) {}
    virtual void push_back (double value) {}
    enum typeId {
        STRING = 0, INT = 1, DOUBLE = 2
    };
};

class StringColumn : public Item
{
public:

    std::string getStringDatum(unsigned int index);
    void push_back(std::string value);
    unsigned int size();
    std::string getRepr(unsigned int index);

private:
    std::vector<std::string> data;

};

class IntColumn : public Item
{
public:
    int getIntDatum(unsigned int index);
    void push_back(int value);
    unsigned int size();
    std::string getRepr(unsigned int index);

private:
    std::vector<int> data;

};

class DoubleColumn : public Item
{
public:
    double getDoubleDatum(unsigned int index);
    void push_back(double value);
    unsigned int size();
    std::string getRepr(unsigned int index);
private:
    std::vector<double> data;
};


//template <typename T>
//class Column : public Item
//{
//public:
//    std::vector<T> data;
//    T getDatum(unsigned int index);
//    void push_back(T value);
//    unsigned int size();
//    std::string getRepr(unsigned int index);

//private:
//    enum typeId {
//        STRING = 0, INT = 1, DOUBLE = 2
//    };
//    std::string stringBuffer;
//    int intBuffer;
//    double doubleBuffer;
//};



//typedef Column<std::string> StringColumn;
//typedef Column<int> IntColumn;
//typedef Column<double> DoubleColumn;




}   // namespace

#endif  // BASE_ITEM_H
