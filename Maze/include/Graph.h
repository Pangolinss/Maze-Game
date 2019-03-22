#ifndef GRAPH_H
#define GRAPH_H
#include"Node.h"
#include<iostream>

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
        virtual ~Graph();

    private:
        Node* origin;
};

#endif // GRAPH_H
