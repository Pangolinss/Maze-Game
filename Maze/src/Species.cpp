#include "Species.h"

//_____________
//|00 |01 |02 |
//|-----------|
//|10 |11 |12 |
//|-----------|
//|20 |21 |22 |
//-------------


Species::Species()
{
    //ctor
    char itarr[4][2] = {{0,1},{1,2},{2,1},{1,0}};
    int arr[4] = {0, 0, 0, 0};
    int n = -1;
    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<3; j++)
        {
            for (int k = 0; k<3; k++)
            {
                cell_types[i][j][k] = 0;
            }
        }
        cell_types[i][1][1] = 1;
    }
    for (int i = 0; i<4; i++)
    {
        ++n;
        cell_types[n][itarr[i][0]][itarr[i][1]] = 1;
    }
    for (int i = 0; i<4; i++)
    {
        for (int j = i+1; j<4; j++)
        {
            ++n;
            cell_types[n][itarr[i][0]][itarr[i][1]] = 1;
            cell_types[n][itarr[j][0]][itarr[j][1]] = 1;
        }
    }
    for (int i = 0; i<4; i++)
    {
        ++n;
        cell_types[n][itarr[(i+1)%4][0]][itarr[(i+1)%4][1]] = 1;
        cell_types[n][itarr[(i+2)%4][0]][itarr[(i+2)%4][1]] = 1;
        cell_types[n][itarr[(i+3)%4][0]][itarr[(i+3)%4][1]] = 1;
    }
    ++n;
    cell_types[n][itarr[0][0]][itarr[0][1]] = 1;
    cell_types[n][itarr[1][0]][itarr[1][1]] = 1;
    cell_types[n][itarr[2][0]][itarr[2][1]] = 1;
    cell_types[n][itarr[3][0]][itarr[3][1]] = 1;

    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<4; j++)
        {
            if (cell_types[i][itarr[j][0]][itarr[j][1]] == 1)
            {
                for (int k = 0; k<15; k++)
                {
                    if (cell_types[k][itarr[(i+2)%4][0]][itarr[(i+2)%4][1]] == 1)
                    {
                        Node* node1 = new Node(arr, 4, cell_types[i]);
                        Node* node2 = new Node(arr, 4, cell_types[k]);
                        if (algorithm.getOrigin() == nullptr)
                        {
                            algorithm.addNode(node1);
                        }
                        algorithm.addNode(node1, node2, arr);
                        algorithm.addNode(node2, node1, arr);
                    }
                }
            }
        }
    }
}

Species::~Species()
{
    //dtor
}
