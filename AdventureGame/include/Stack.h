#ifndef STACK_H
#define STACK_H
#include"Element.h"

template<typename T>
class Stack
{
    private:
        Element<T>* top;
    public:
        Stack();
        void push(T);
        T peek();
        Element<T>* pop();
};

#endif // STACK_H
