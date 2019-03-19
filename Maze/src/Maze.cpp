#include "Maze.h"

Maze::Maze()
{

}

void Maze::generateMaze()
{
    int coor[2];
    coor[0] = rand() % SIZE;
    coor[1] = rand() % SIZE;
    buildMaze(coor);
}

void Maze::buildMaze(int coor[])
{
    int move_pool[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int ccopy[2];
    int makeLoop = 0;
    grid[coor[0]][coor[1]].visit = true;
    shuffle(move_pool, 4);
    for (int i = 0; i<4; i++)
    {
        ccopy[0] = coor[0] + move_pool[i][0];
        ccopy[1] = coor[1] + move_pool[i][1];
        if (ccopy[0]>=0 && ccopy[0]<SIZE && ccopy[1]>=0 && ccopy[1]< SIZE)
        {
            makeLoop = rand()%20;
            if (grid[ccopy[0]][ccopy[1]].visit == false || makeLoop == 0)
            {
                int dir = -1;
                if (move_pool[i][0] == 0 && move_pool[i][1] == 1){dir = 0;}
                else if (move_pool[i][0] == 0 && move_pool[i][1] == -1){dir = 1;}
                else if (move_pool[i][0] == 1 && move_pool[i][1] == 0){dir = 2;}
                else if (move_pool[i][0] == -1 && move_pool[i][1] == 0){dir = 3;}
                grid[coor[0]][coor[1]].pointarr[dir] = &grid[ccopy[0]][ccopy[1]];
                switch (dir)
                {
                    case 0: dir = 1; break;
                    case 1: dir = 0; break;
                    case 2: dir = 3; break;
                    case 3: dir = 2; break;
                    default: break;
                }
                grid[ccopy[0]][ccopy[1]].pointarr[dir] = &grid[coor[0]][coor[1]];
                buildMaze(ccopy);
            }
        }
    }
    return;
}

void Maze::print()
{
    char arr[2*SIZE+1][2*SIZE+1];
    for (int i = 0; i<2*SIZE+1; i++)
    {
        for (int j = 0; j<2*SIZE+1; j++)
        {
            arr[i][j] = '#';
        }
    }
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            for (int k = 0; k<4; k++)
            {
                arr[2*i+1][2*j+1] = ' ';
                int a[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
                if (grid[i][j].pointarr[k] != nullptr)
                {
                    arr[2*i+1+a[k][0]][2*j+1+a[k][1]] = ' ';
                }
            }
        }
    }
    for (int i = 0; i<2*SIZE+1; i++)
    {
        for (int j = 0; j<2*SIZE+1; j++)
        {
            std::cout<<arr[i][j];
        }
        std::cout<<std::endl;
    }
}

void Maze::shuffle(int arr[][2], int arr_size)
{
    int temp[2];
    int r1;
    int r2;
    for (int i = 0; i<2000; i++)
    {
        r1 = rand()%arr_size;
        r2 = rand()%arr_size;
        temp[0] = arr[r1][0];
        temp[1] = arr[r1][1];
        arr[r1][0] = arr[r2][0];
        arr[r1][1] = arr[r2][1];
        arr[r2][0] = temp[0];
        arr[r2][1] = temp[1];
    }
}

Maze::~Maze()
{
    //dtor
}
