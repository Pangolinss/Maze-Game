#ifndef ELEMENT_H
#define ELEMENT_H
#include<string>
#include<assert.h>
#include<iostream>

class Node;
template <typename T>
class LinkList;

template<typename T>
class Element
{
    private:
        Element* next;
        Element* before;
        T* value;
    public:
        Element();//Default constructor

        //Get and Set functions
        void setValue (T);
        void setNext(Element*);
        void setBefore(Element*);
        T getValue() const;
        T* getValuep() const;
        Element* getNext() const;
        Element* getBefore() const;

        //Other constructors, usually don't use them
        Element(T, Element*);
        Element(T, Element*, Element*);

        //Basically a set function, points the elements to other things
        void point(Element*, Element*);

        //Assignment and comparison operator
        void operator=(Element);
        bool operator==(Element);

        //Functions that don't work
        void eCopyNext(Element*, Element*, Element*);//An attempt to recursively copy things, dosen't work use the LinkList assignment operator

        virtual ~Element();//Default destructor
};

#endif // ELEMENT_H
