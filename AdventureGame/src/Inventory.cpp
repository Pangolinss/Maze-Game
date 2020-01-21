#include "Inventory.h"

Inventory::Inventory()
{
    //ctor
}

Inventory::Inventory(int n, Items*(*_itemList)[NUM_ITEMS])
{
    inv_size = n;
    inv = new Items*[n];
    for (int i = 0; i<n; i++)
    {
        inv[i] = nullptr;
    }
    itemList = _itemList;
}

Inventory::~Inventory()
{
    //dtor
}

bool Inventory::addItem(Items item)
{
    for (int i = 0; i<inv_size; i++)
    {
        if (inv[i] != nullptr)
        {
            if (*(inv[i]) == item)
            {
                return true;
            }
        }
    }
    for (int i= 0; i<inv_size; i++)
    {
        if (inv[i] == nullptr)
        {
            inv[i] = new Items;
            *inv[i] = item;
            return true;
        }
    }
    return false;
}

bool Inventory::addItem(int n)
{
    for (int i= 0; i<0; i++)
    {
        if (inv[i] == nullptr)
        {
            inv[i] = new Items;
            *inv[i] = *(*itemList[n]);
            return true;
        }
    }
    return false;
}

bool Inventory::removeItem(int n)
{
    if (inv[n] == nullptr)
    {
        return false;
    }
    else
    {
        delete inv[n];
        inv[n] = nullptr;
    }
    return true;
}

bool Inventory::playerHasItem(Items::Item _item)
{
    for (int i = 0; i<inv_size; i++)
    {
        if (inv[i] != nullptr)
        {
            if (inv[i]->getId() == _item)
            {
                return true;
            }
        }
    }
    return false;
}
