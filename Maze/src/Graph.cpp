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
    onThis->addConnection(node);
    onThis->addMagnitude(mag);
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
    if (node->visit == false)
    {
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                std::cout<<node->getShape()[i][j];
            }
            std::cout<<std::endl;
        }
        std::cout<<"Is connected to "<<std::endl<<std::endl;
        int n = 0;
        node->visit = true;
        while(node->getConnection(n) != nullptr)
        {
            print(node->getConnection(n));
            n++;
        }
    }
    return;
}

void Graph::addtoNodeList(Node* node)
{
    allNodes.append(node);
}

Node* Graph::iterateNodes(int n)
{
    if (allNodes[n]->getValuep() != nullptr)
    {
        return allNodes[n]->getValue();
    }
    else {return nullptr;}
}

Graph::~Graph()
{
    //dtor
}
