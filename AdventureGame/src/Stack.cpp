#include "Stack.h"

template<typename T>
Stack<T>::Stack()
{
    top = nullptr;
}

template<typename T>
void Stack<T>::push(T _val)
{
    Element<T>* newTop;
    newTop = new Element<T> (_val, top);
    top = newTop;
}

template<typename T>
T Stack<T>::peek()
{
    return top->getValue();
}

template<typename T>
Element<T>* Stack<T>::pop()
{
    if (top != nullptr)
    {
        Element<T>* ele = top;
        top = top->getNext();
        ele->setNext(nullptr);
        return ele;
    }
    else
    {
        assert(false && "Stack::pop() cannot return nullpntr");
        return 0;
    }
}

template class Stack <std::string>;
template class Stack <int>;
template class Stack <char>;
template class Stack <bool>;
template class Stack <double>;
template class Stack <int*>;
