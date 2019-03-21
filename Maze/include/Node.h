#ifndef NODE_H
#define NODE_H
#include "LinkList.h"

class Node
{
    public:
        Node();
        Node(int[], int, char[3][3]);
        Node* getConnection(int);
        int* getMagnitude(int);

        void addConnection(Node*);
        void addMagnitude(int*);

        int* getValue();

        virtual ~Node();

    private:
        LinkList<int*> magnitude;
        LinkList<Node*> connections;
        int* value;
        char shape[3][3];

};

#endif // NODE_H
