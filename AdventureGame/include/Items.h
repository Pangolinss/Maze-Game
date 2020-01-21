#ifndef ITEMS_H
#define ITEMS_H
#define NUM_ITEMS 20
#include<SFML/Graphics.hpp>
#include<string>
//not used
class Items
{
    public:
        enum Item{Key};
        static Item item;
        Items();
        Items(Item, std::string, std::string);
        virtual ~Items();
        int getId(){return id;}
        std::string getName(){return name;}
        std::string getImageStr(){return image_str;}

        void setId(Item a){id = a;}
        void setName(std::string a){name = a;}
        void setImageStr(std::string a){image_str = a;}

        friend void createItemList(Items* item[NUM_ITEMS]);

        void operator=(Items);
        bool operator==(Items);

        friend class ItemList;

    protected:

    private:
        Item id;
        std::string name;
        std::string image_str;
        sf::Sprite sprite;

};


#endif // ITEMS_H
