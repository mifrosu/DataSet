#include "item.h"
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <cmath>

namespace mos {

Item::~Item() {}

std::string Item::getStringDatum(unsigned int index)
{
    return " ";
}

int Item::getIntDatum(unsigned int index)
{
    return -1;
}

double Item::getDoubleDatum(unsigned int index)
{
    return std::numeric_limits<double>::quiet_NaN();
}

std::vector<unsigned int> Item::findValue(const std::string& value)
{
    std::vector<unsigned int> indexList;
    return indexList;
}

std::vector<unsigned int> Item::findValue(int value)
{
    std::vector<unsigned int> indexList;
    return indexList;
}

std::vector<unsigned int> Item::findValue(double value)
{
    std::vector<unsigned int> indexList;
    return indexList;
}


// --- StringColumn

std::string StringColumn::getRepr(unsigned int index) {
    assert(index < data.size());
    std::stringstream ss;
    ss << data[index];
    return ss.str();
}

std::string StringColumn::getStringDatum(unsigned int index) {
    if (index < data.size()) {
        return data[index];
    }
    else { return " "; }
}

void StringColumn::push_back(std::string value) {
    data.push_back(value);
}

unsigned int StringColumn::size() {
    return data.size();
}

std::vector<unsigned int> StringColumn::findValue(const std::string& value)
{
    std::vector<unsigned int> indexList;
    std::vector<std::string>::iterator iter = data.begin();
    std::vector<std::string>::iterator iterEnd = data.end();

    while(iter != iterEnd) {
        iter = std::find(iter, iterEnd, value);
        if (iter != iterEnd) {
            indexList.push_back(std::distance(data.begin(),iter));
            ++iter;
        }
    }
    return indexList;
}

void StringColumn::getData(std::vector<std::string> &store)
{
    store = data;
}


// --- IntColumn

std::string IntColumn::getRepr(unsigned int index) {
    assert(index < data.size());
    std::stringstream ss;
    ss << data[index];
    return ss.str();
}

int IntColumn::getIntDatum(unsigned int index) {
    if (index < data.size()) {
        return data[index];
    }
    else { return -1; }
}

void IntColumn::push_back(int value) {
    data.push_back(value);
}

unsigned int IntColumn::size() {
    return data.size();
}

std::vector<unsigned int> IntColumn::findValue(int value)
{
    std::vector<unsigned int> indexList;
    std::vector<int>::iterator iter = data.begin();
    std::vector<int>::iterator iterEnd = data.end();

    while(iter != iterEnd) {
        iter = std::find(iter, iterEnd, value);
        if (iter != iterEnd) {
            indexList.push_back(std::distance(data.begin(),iter));
            ++iter;
        }
    }
    return indexList;
}

void IntColumn::getData(std::vector<int> &store)
{
    store = data;
}

// --- DoubleColumn

std::string DoubleColumn::getRepr(unsigned int index) {
    assert(index < data.size());
    std::stringstream ss;
    ss << data[index];
    return ss.str();
}

double DoubleColumn::getDoubleDatum(unsigned int index) {
    if (index < data.size()) {
        return data[index];
    }
    else { return std::numeric_limits<double>::quiet_NaN(); }
}

void DoubleColumn::push_back(double value)
{
    data.push_back(value);
}

unsigned int DoubleColumn::size() {
    return data.size();
}

bool DoubleColumn::compareDouble(double a, double b)
{
    if (a == b) {
        return true;
    }
    else {
        double diff = fabs(a-b);
        if (a == 0 || b == 0 || diff < epsilon) {
            return (diff < epsilon);
        }
        else {
            double abs_a = fabs(a);
            double abs_b = fabs(b);
            return (diff/(abs_a + abs_b) < epsilon);
        }
    }
}

std::vector<unsigned int> DoubleColumn::findValue(double value)
{
    std::vector<unsigned int> indexList;
    std::vector<double>::iterator iter = data.begin();
    std::vector<double>::iterator iterEnd = data.end();

    while(iter != iterEnd) {
        if (compareDouble(*iter, value)) {
            indexList.push_back(std::distance(data.begin(),iter));
        }
        ++iter;
    }
    return indexList;
}

std::vector<unsigned int> DoubleColumn::findValue(double value,
                                            bool (*compare)(double,double))
{
    std::vector<unsigned int> indexList;
    std::vector<double>::iterator iter = data.begin();
    std::vector<double>::iterator iterEnd = data.end();

    while(iter != iterEnd) {
        if (compare(*iter, value)) {
            indexList.push_back(std::distance(data.begin(),iter));
        }
        ++iter;
    }
}

void DoubleColumn::getData(std::vector<double> &store)
{
    store = data;
}



//template <typename T>
//T Column<T>::getDatum(unsigned int index)
//{
//    assert(index < data.size());
//    return data[index];
//}

////template <typename T>
////int Column<T>::getIntDatum(unsigned int index)
////{
////    // for other than Column<int>
////    return -1;
////}

//template <typename T>
//std::string Column<T>::getRepr(unsigned int index)
//{
//    assert(index < data.size());
//    std::stringstream ss;
//    ss << data[index];
//    return ss.str();
//}

//template <typename T>
//void Column<T>::push_back(T value)
//{
//    data.push_back(value);
//}

//template <typename T>
//unsigned int Column<T>::size()
//{
//    return data.size();
//}

//template class Column<std::string>;
//template class Column<int>;
//template class Column<double>;

////template<>
////int Column<int>::getIntDatum(unsigned int index)
////{
////    assert(index < data.size());
////    if (type == INT) {
////        return data[index];
////    }
////    else {
////        return -1;
////    }
////}

}





