#include "Items.h"

Items::Items()
{
    //ctor
}

Items::Items(Item _id, std::string _name, std::string _image_str)
{
    id = _id;
    name = _name;
    image_str = _image_str;
}

Items::~Items()
{
    //dtor
}

void Items::operator=(Items item)
{
    id = item.id;
    name = item.name;
    image_str = item.image_str;
}

bool Items::operator==(Items item)
{
    return (id == item.id);
}


void createItemList(Items* item[NUM_ITEMS])
{
    for (int i = 0; i<NUM_ITEMS; i++)
    {
        item[i] = nullptr;
    }
    item[0] = new Items(Items::Key, "Key", "bin\\Release\\common\\Items\\key.png");
}
