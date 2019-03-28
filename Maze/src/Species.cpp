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
    int itarr[4][2] = {{0,1},{1,2},{2,1},{1,0}};
    int arr[4] = {0, 0, 0, 0};
    int n = -1;
    Node** node_list;
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

    node_list = new Node*[15];
    for (int i = 0; i<15; i++)
    {
        node_list[i] = new Node(arr, 4, cell_types[i]);
        algorithm.addtoNodeList(node_list[i]);
    }
    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<4; j++)
        {
            if (cell_types[i][itarr[j][0]][itarr[j][1]] == 1)
            {
                for (int k = 0; k<15; k++)
                {
                    if (cell_types[k][itarr[(j+2)%4][0]][itarr[(j+2)%4][1]] == 1)
                    {
                        Node* node1 = node_list[i];
                        Node* node2 = node_list[k];
                        if (algorithm.getOrigin() == nullptr)
                        {
                            algorithm.addNode(node1);
                        }
                        algorithm.addNode(node1, node2, arr);
                        algorithm.addNode(node2, node1, arr);
                       // std::cout<<i<<"and"<<k<<std::endl;
                    }
                }
            }
        }
    }
}

LinkList<int*> Species::getGenome(int i)
{
    return genome[i];
}

void Species::setGenome(int i, int n, int* k)
{
    genome[i][n]->setValue(k);
}

void Species::print()
{
    algorithm.print(algorithm.getOrigin());
}

void Species::createAlgorithm()
{
    int r[4];
    int* ra;
    int* temp;
    for (int n = 0; n<15; n++)
    {

        int m = 0;
        temp = new int[4];
        for (int i = 0; i<4; i++)
        {
            r[i] = (rand()%2001)-1000;
            temp[i] = r[i];
        }
        genome[n].append(temp);
        algorithm.iterateNodes(n)->setValue(r, 4);
        while (algorithm.iterateNodes(n)->getConnection(m) != nullptr)
        {
            ra = new int[4];
            temp = new int[4];
            for (int i = 0; i<4; i++)
            {
                ra[i] = (rand()%2001)-1000;
                temp[i] = ra[i];
            }
            algorithm.iterateNodes(n)->addMagnitude(ra);
            genome[n].append(temp);
            m++;
        }
    }
}

void Species::outputGenome()
{
    for (int i = 0; i<15; i++)
    {
        int m = 0;
        while (genome[i][m] != nullptr)
        {
            for (int n = 0; n<4; n++)
            {
                std::cout<<genome[i][m]->getValue()[n]<<" ";
            }
            m++;
        }
        std::cout<<std::endl;
    }
}

Species Species::meiosis(Species species)//itself is parent A, the argument is parent B.
{
    int r;
    Species child_species;
    child_species.createAlgorithm();
    for (int i = 0; i<15; i++)
    {
        int n = 0;
        while (genome[i][n] != nullptr)
        {
            int* temp;
            r = rand()%100;
            if (r == 0)//mutation occurs
            {
            }
            else if(r != 0 && r<50)//crossover from parent A
            {
                temp = genome[i][n]->getValue();
                child_species.setGenome(i, n, temp);
            }
            else if (r>50)//crossover from parent B
            {
                temp = species.getGenome(i)[n]->getValue();
                child_species.setGenome(i, n, temp);
            }
            n++;
        }
    }
    return child_species;
}

Species::~Species()
{
    //dtor
}
