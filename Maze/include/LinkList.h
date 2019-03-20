#ifndef LINKLIST_H
#define LINKLIST_H
#include"Element.h"

template<typename T>
class LinkList
{
    public:
        LinkList();//Default constructor

        //Append and Add
        void append(T);//add element to the end of a link list
        void append(Element<T>*);
        void add(T, Element<T>*);//add element to the front of an element
        void add(Element<T>*, Element<T>*);

        //Links two elements
        void linkElements(Element<T>*, Element<T>*);//links to elements together

        //Get and set functions
        Element<T>* getFirst() const;
        Element<T>* getLast() const;

        //Finds a certain element, returns a pointer
        Element<T>* lfind(T);
        Element<T>* lfindi(int);//Returns a pointer to an element given a position

        //Removing functions
        T lremove(Element<T>*);//Removes an element

        //Assingment operator
        void operator=(LinkList);

        //Finding operator. Once I template these data structures I am going to make this return the actual value rather than a pointer
        Element<T>* operator[](int);

        virtual ~LinkList();

    private:
        Element<T>* first;
        Element<T>* last;
};


#endif // LINKLIST_H
