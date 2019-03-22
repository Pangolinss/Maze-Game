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

void Graph::addNode(Node* onThis, Node* _node, int* mag)
{
    Node* node;
    node = _node;
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

void Graph::print(Node* node)
{
    std::cout<<node->visit<<std::endl;
    if (node->visit == false)
    {
        int n = 0;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                std::cout<<node->getShape()[i][j];
            }
            std::cout<<std::endl;
        }
        node->visit = true;
        while(node->getConnection(n) != nullptr)
        {
            print(node->getConnection(n));
            n++;
        }
    }
    return;
}

Graph::~Graph()
{
    //dtor
}
