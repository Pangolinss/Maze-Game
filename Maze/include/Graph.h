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
        void print(Node* node);
        void addtoNodeList(Node*);
        Node* iterateNodes(int);
        virtual ~Graph();

    private:
        Node* origin;
        LinkList<Node*> allNodes;
};

#endif // GRAPH_H
