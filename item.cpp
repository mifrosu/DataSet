#include "item.h"
#include <limits>
#include <cmath>

namespace mos {

Item::~Item() {}

int Item::getIntDatum(unsigned int index)
{
    return -1;
}

template <typename T>
T Column<T>::getDatum(unsigned int index)
{
    assert(index < data.size());
    return data[index];
}

//template <typename T>
//int Column<T>::getIntDatum(unsigned int index)
//{
//    // for other than Column<int>
//    return -1;
//}

template <typename T>
std::string Column<T>::getRepr(unsigned int index)
{
    assert(index < data.size());
    std::stringstream ss;
    ss << data[index];
    return ss.str();
}

template <typename T>
void Column<T>::push_back(T value)
{
    data.push_back(value);
}

template <typename T>
unsigned int Column<T>::size()
{
    return data.size();
}

template class Column<std::string>;
template class Column<int>;
template class Column<double>;

//template<>
//int Column<int>::getIntDatum(unsigned int index)
//{
//    assert(index < data.size());
//    if (type == INT) {
//        return data[index];
//    }
//    else {
//        return -1;
//    }
//}

}





