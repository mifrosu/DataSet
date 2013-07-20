#include "item.h"
#include <limits>
#include <cmath>

namespace mos {

Item::~Item() {}

int Item::getIntDatum(unsigned int index)
{
    return -1;
}

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





