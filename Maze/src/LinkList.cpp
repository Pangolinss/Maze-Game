#include "LinkList.h"

template<typename T>
LinkList<T>::LinkList()
{
    first = nullptr;
    last = nullptr;
}

template<typename T>
void LinkList<T>::append(T _str)
{
    Element<T>* ele;
    ele = new Element<T>(_str, last, nullptr);
    if (last != nullptr)
    {
        last->setBefore(ele);
    }
    if (first == nullptr)
    {
        first = ele;
    }
    last = ele;
    return;
}

template<typename T>
void LinkList<T>::append(Element<T>* ele)
{
    ele->point(last, nullptr);
    if (last != nullptr)
    {
        last->setBefore(ele);
    }
    if (first == nullptr)
    {
        first = ele;
    }
    last = ele;
    return;
}

template<typename T>
void LinkList<T>::add(T str, Element<T>* inFrontOfThis)
{
    Element<T>* ele;
    ele = new Element<T>(str, inFrontOfThis->getNext(), inFrontOfThis);
    if (inFrontOfThis != nullptr)
    {
        if (inFrontOfThis == first)
        {
            inFrontOfThis->setNext(ele);
            first = ele;
        }
        else
        {
            inFrontOfThis->getNext()->setBefore(ele);
            inFrontOfThis->setNext(ele);
        }
    }
    else
    {
        //Should they be able to add a nullpntr to a list?
        //Im going to go with no, if they want to split a list ill make a function for that
    }
}

template<typename T>
void LinkList<T>::linkElements(Element<T>* ele1, Element<T>* ele2)
{
    ele1->setBefore(ele2);
    ele2->setNext(ele1);
}

template<typename T>
Element<T>* LinkList<T>::getFirst() const
{
    return first;
}

template<typename T>
Element<T>* LinkList<T>::getLast() const
{
    return last;
}

template<typename T>
Element<T>* LinkList<T>::lfindi(int num)
{
    Element<T>* ele;
    ele = first;
    int i = 0;
    while (i<num && ele != nullptr)
    {
        ele = ele->getBefore();
        if (ele == nullptr)
        {
            return nullptr;
        }
        i++;
    }
    return ele;
}

template<typename T>
T LinkList<T>::lremove(Element<T>* ele)
{
    if (ele != nullptr)
    {
        T val = ele->getValue();
        if (first != nullptr && last != nullptr)
        {
            if (ele == first && ele == last)
            {
                first = nullptr;
                last = nullptr;
            }
            else if (ele->getNext() != nullptr && ele->getBefore() != nullptr)
            {
                ele->getBefore()->setNext(ele->getNext());
                ele->getNext()->setBefore(ele->getBefore());
            }
            else if (ele == first)
            {
                first = ele->getBefore();
                ele->getBefore()->setNext(nullptr);
            }
            else if (ele == last)
            {
                last = ele->getNext();
                ele->setNext(nullptr);
            }
            ele->point(nullptr, nullptr);
            return val;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

template<typename T>
void LinkList<T>::operator=(LinkList<T> other)
{
    Element<T>* point;
    Element<T>* _list = new Element<T>;
    Element<T>* actualList;

    point = other.getLast();

    *_list = *point;
    actualList = _list;


    point = point->getNext();
    _list = new Element<T>;

    actualList->setNext(_list);
    actualList->setBefore(nullptr);
    _list->setBefore(actualList);

    last = actualList;

    while (point != other.getFirst())
    {
        *_list = *point;
        actualList = _list;

        point = point->getNext();
        _list = new Element<T>;

        actualList->setNext(_list);
        _list->setBefore(actualList);
    }
    *_list = *point;
    first = _list;
}

template<typename T>
Element<T>* LinkList<T>::operator[](int num)
{
    Element<T>* ele;
    ele = first;
    int i = 0;
    while (i<num && ele != nullptr)
    {
        ele = ele->getBefore();
        if (ele == nullptr)
        {
            return nullptr;
        }
        i++;
    }
    return ele;
}

template<typename T>
LinkList<T>::~LinkList<T>()
{
    //dtor
}

template class LinkList <std::string>;
template class LinkList <int>;
template class LinkList <char>;
template class LinkList <bool>;
template class LinkList <double>;
template class LinkList <int*>;
template class LinkList <Node*>;
template class LinkList <LinkList<int*>*>;
