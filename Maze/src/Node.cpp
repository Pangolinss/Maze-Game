#include "Node.h"

Node::Node()
{
    //ctor
}

Node::Node(int arr[], int arrsize, char _shape[3][3])
{
    value = new int[arrsize];
    for (int i = 0; i<arrsize; i++)
    {
        value[i] = arr[i];
    }
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            shape[i][j] = _shape[i][j];
        }
    }
}

Node* Node::getConnection(int i)
{
    return connections[i]->getValue();
}

int* Node::getMagnitude(int i)
{
    return magnitude[i]->getValue();
}

void Node::addConnection(Node* _node)
{
    connections.append(_node);
}

void Node::addMagnitude(int* vec)
{
    magnitude.append(vec);
}

int* Node::getValue()
{
    return value;
}

Node::~Node()
{
    //dtor
}
