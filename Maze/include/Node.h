#ifndef NODE_H
#define NODE_H
#include "LinkList.h"

class Node
{
    public:
        Node();
        Node(int[], int, int[3][3]);
        Node* getConnection(int);
        int* getMagnitude(int);

        void setConnection(int, Node*);
        void setMagnitude(int, int*);

        void addConnection(Node*);
        void addMagnitude(int*);

        int* getValue();
        int** getShape();

        void setValue(int[], int);
        void setShape();

        virtual ~Node();
        bool visit;

    private:
        LinkList<int*> magnitude;
        LinkList<Node*> connections;
        int* value;
        int shape[3][3];

};

#endif // NODE_H
