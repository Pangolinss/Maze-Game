#ifndef INVENTORY_H
#define INVENTORY_H
#include<string>
#include"Items.h"
//not used
class Being;
class Player;
class Monster;
class Inventory
{
    public:
        Inventory();
        Inventory(int n, Items* (*_itemList)[NUM_ITEMS]);
        virtual ~Inventory();

        int getInvSize(){return inv_size;}

        void resizeInv(int);
        bool addItem(Items);
        bool addItem(int);
        bool removeItem(int);
        int* seeItems();
        bool playerHasItem(Items::Item);

    private:
        int inv_size;
        Items** inv;
        Items* (*itemList)[NUM_ITEMS];//a pointer to an array of pointers, really just a pointer to an array of items
};

#endif // INVENTORY_H
