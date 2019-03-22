#include "Node.h"

Node::Node()
{
    //ctor
    visit = false;
}

Node::Node(int arr[], int arrsize, int _shape[3][3])
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
    visit = false;
}

Node* Node::getConnection(int i)
{
    if (connections[i]->getValuep() != nullptr)
    {
        return *(connections[i]->getValuep());
    }
    else
    {
        return nullptr;
    }
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

int** Node::getShape()
{
    int** arr = new int*[3];
    for (int i = 0; i<3; i++)
    {
        arr[i] = new int[3];
    }
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            arr[i][j] = shape[i][j];
        }
    }
    return arr;
}

Node::~Node()
{
    //dtor
}
