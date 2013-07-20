#include "item.h"
#include <iostream>
#include <limits>
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


// --- IntColumn

std::string IntColumn::getRepr(unsigned int index) {
    std::cout << "size:" << data.size() << std::endl;
    std::cout << "--- " << index << " ---" << std::endl;
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





