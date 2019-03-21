#include "Graph.h"

Graph::Graph()
{
    origin = nullptr;
    //ctor
}

void Graph::setOrigin(Node* node)
{
    origin = node;
}

Node* Graph::getOrigin()
{
    return origin;
}

void Graph::addNode(Node* onThis, Node* node, int* mag)
{
    if (origin == nullptr)
    {
        origin = onThis;
    }
    else
    {
        onThis->addConnection(node);
        onThis->addMagnitude(mag);
    }
}

void Graph::addNode(Node* onThis)
{
    if (origin == nullptr)
    {
        origin = onThis;
    }
}

int* Graph::getNodeConMag(Node* originNode, Node* node)
{
    Node* nodePoint;
    nodePoint = originNode;
    int i = 0;
    while (nodePoint != nullptr)
    {
        nodePoint = originNode->getConnection(i);
        if (nodePoint == node)
        {
            return originNode->getMagnitude(i);
        }
        i++;
    }
    return nullptr;
}

Graph::~Graph()
{
    //dtor
}
