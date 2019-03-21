#ifndef GRAPH_H
#define GRAPH_H
#include"Node.h"

class Graph
{
    public:
        Graph();
        void setOrigin(Node*);
        Node* getOrigin();
        void addNode(Node*, Node*, int*);
        void addNode(Node*);
        void getNode(int);
        int* getNodeConMag(Node*, Node*);
        virtual ~Graph();

    private:
        Node* origin;
};

#endif // GRAPH_H
