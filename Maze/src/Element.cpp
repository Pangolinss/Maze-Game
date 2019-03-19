#include "Element.h"

template <typename T>
Element<T>::Element()
{
    value = new T;
    next = nullptr;
    before = nullptr;
}

template <typename T>
void Element<T>::setValue (T _val)
{
    *value = _val;
}

template <typename T>
void Element<T>::setBefore(Element<T>* ele)
{
    before = ele;
}

template <typename T>
void Element<T>::setNext(Element<T>* ele)
{
    next = ele;
}

template <typename T>
T Element<T>::getValue() const
{
    if (this == nullptr)
    {
        assert(false && "Element::getValue(): calling getValue() on a nullpntr");
    }
    else
    {
        return *value;
    }
}

template <typename T>
Element<T>* Element<T>::getNext() const
{
    return (this==nullptr) ? (nullptr) : (next);
}

template <typename T>
Element<T>* Element<T>::getBefore() const
{
    return (this==nullptr) ? (nullptr) : (before);
}

template <typename T>
Element<T>::Element(T _val, Element<T>* _ele)
{
    value = new T;
    *value = _val;
    next = _ele;
}

template <typename T>
Element<T>::Element(T _val, Element<T>* ele1, Element<T>* ele2)
{
    value = new T;
    *value = _val;
    next = ele1;
    before = ele2;
}

template <typename T>
void Element<T>::point(Element<T>* ele1, Element<T>* ele2)
{
    next = ele1;
    before = ele2;
}

template <typename T>
void Element<T>::operator=(Element<T> other)
{
    next = other.getNext();
    before = other.getBefore();
    *value = other.getValue();
}

template <typename T>
bool Element<T>::operator==(Element<T> other)
{
    if (next == other.getNext() && before == other.getBefore() && *value == other.getValue())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

template <typename T>
void Element<T>::eCopyNext(Element<T>* ele, Element<T>* _first, Element<T>* _last)
{
    Element<T>* eleNext;
    eleNext = new Element<T>(0, nullptr, nullptr);
    ele = new Element<T>(0, nullptr, nullptr);
    *ele = *_last;
    if (_last->getBefore() == nullptr)
    {
        ele->setBefore(nullptr);
    }
    if (_last == _first)
    {
         ele->setNext(nullptr);
         return;
    }
    else
    {
        eCopyNext(eleNext, _first, _last->getNext());
        eleNext->setBefore(ele);
        ele->setNext(eleNext);
        return;
    }
}

template<typename T>
Element<T>::~Element<T>()
{
    //dtor
}

template class Element <std::string>;
template class Element <int>;
template class Element <char>;
template class Element <bool>;
template class Element <double>;
template class Element <int*>;
