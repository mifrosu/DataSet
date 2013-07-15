#ifndef BASE_ITEM_H
#define BASE_ITEM_H

namespace mos_dataset {

class Item
{
public:

    virtual ~Item();
    int type;
    int currentIndex;
    int futureIndex;

private:
    Item();
};

class StringItem : public Item
{
    std::string datum;

};

class IntItem : public Item
{
    int datum;
};

class DoubleItem : public Item
{
    double datum;
};

}   // namespace

#endif BASE_ITEM_H
