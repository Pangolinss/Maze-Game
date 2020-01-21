#include "Maze.h"

struct Cell;

Maze::Maze()
{
    finish = &grid[SIZE-1][SIZE-1];
    dir = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            grid[i][j].coor[0] = i;
            grid[i][j].coor[1] = j;
            grid[i][j].visit = false;
            for (int k = 0; k<4; k++)
            {
                grid[i][j].pointarr[k] = nullptr;
                grid[i][j].cross.mark[k] = 0;
            }
            grid[i][j].cross.isCross= false;
            grid[i][j].isDoor = false;
            grid[i][j].isKey = false;
        }
    }
    ava_loc = &grid[0][0];
}

void Maze::generateMaze()
{
    int coor[2];
    coor[0] = rand() % SIZE;//randomly picks start
    coor[1] = rand() % SIZE;
    buildMaze(coor);
}

void Maze::buildMaze(int coor[])
{
    //Not going to lie, I wrote this program
    int move_pool[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};//to iterate through going 4 direction
    int ccopy[2];
    int makeLoop = 0;
    grid[coor[0]][coor[1]].visit = true;//sets cell to be true
    shuffle(move_pool, 4);
    for (int i = 0; i<4; i++)
    {
        ccopy[0] = coor[0] + move_pool[i][0];//for each direction it sets ccopy to be at the adjacent cell
        ccopy[1] = coor[1] + move_pool[i][1];
        if (ccopy[0]>=0 && ccopy[0]<SIZE && ccopy[1]>=0 && ccopy[1]< SIZE)//if the cell is within the bounds
        {
            makeLoop = rand()%40;//allows some loops
            if (grid[ccopy[0]][ccopy[1]].visit == false || makeLoop == 0)//checks if you have been in that cell before
            {
                int dir = -1;
                if (move_pool[i][0] == 0 && move_pool[i][1] == 1){dir = 0;}//checks if a direction is valid and picks that direction
                else if (move_pool[i][0] == 0 && move_pool[i][1] == -1){dir = 1;}
                else if (move_pool[i][0] == 1 && move_pool[i][1] == 0){dir = 2;}
                else if (move_pool[i][0] == -1 && move_pool[i][1] == 0){dir = 3;}
                grid[coor[0]][coor[1]].pointarr[dir] = &grid[ccopy[0]][ccopy[1]];
                switch (dir)//if two cells are connected the opposite direction of the other cell must also connect with you, so this just calcs the inverse
                {
                    case 0: dir = 1; break;
                    case 1: dir = 0; break;
                    case 2: dir = 3; break;
                    case 3: dir = 2; break;
                    default: break;
                }
                grid[ccopy[0]][ccopy[1]].pointarr[dir] = &grid[coor[0]][coor[1]];//sets pointer to point to your cell
                buildMaze(ccopy);//makes a maze again centered here
            }
        }
    }
    return;
}

void Maze::print()//couts a maze
{
    char arr[2*SIZE+1][2*SIZE+1];
    for (int i = 0; i<2*SIZE+1; i++)
    {
        for (int j = 0; j<2*SIZE+1; j++)
        {
            arr[i][j] = 219;
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
                if (grid[i][j].pointarr[k] != nullptr)//if its nullpntr it means its a wall
                {
                    arr[2*i+1+a[k][0]][2*j+1+a[k][1]] = ' ';//pasable terrain
                }
            }
            if (grid[i][j].isDoor)
            {
                arr[2*i+1][2*j+1] = 'D';//door
            }
            if (grid[i][j].isKey)
            {
                arr[2*i+1][2*j+1] = 'K';//key
            }
            if (ava_loc == &grid[i][j])
            {
                arr[2*i+1][2*j+1] = 1;//you :)
            }
            if (finish == &grid[i][j])
            {
                arr[2*i+1][2*j+1] = '@';//exit
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

void Maze::shuffle(int arr[][2], int arr_size)//shuffles an array
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

void Maze::makeMazeArr(int arr[2*SIZE+1][2*SIZE+1])//turns maze into an array
{
    for (int i = 0; i<2*SIZE+1; i++)
    {
        for (int j = 0; j<2*SIZE+1; j++)
        {
            arr[i][j] = 1;
        }
    }
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            for (int k = 0; k<4; k++)
            {
                arr[2*i+1][2*j+1] = 0;
                int a[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
                if (grid[i][j].pointarr[k] != nullptr)
                {
                    arr[2*i+1+a[k][0]][2*j+1+a[k][1]] = 0;
                }
            }
            if (grid[i][j].isDoor == true)
            {
                arr[2*i+1][2*j+1] = 2;
            }
        }
    }
}

bool Maze::checkMove(int n)//checks if a move is valid
{
    if (ava_loc->pointarr[n] != nullptr)
    {
        ava_loc = ava_loc->pointarr[n];
        return true;
    }

    return false;
}

bool Maze::checkMove2(int n)//checks if a move is valid and i you have visited it before
{
    if (ava_loc->pointarr[n] != nullptr)
    {
        if (ava_loc->pointarr[n]->visit == false)
        {
            ava_loc = ava_loc->pointarr[n];
            return true;
        }
    }
    return false;
}

bool Maze::checkMove3(int n)//checks if a move is valid, if you visited it before, or if its a door
{
    if (ava_loc->pointarr[n] != nullptr)
    {
        if (ava_loc->pointarr[n]->visit == false)
        {
            if (ava_loc->pointarr[n]->isDoor == false || (ava_loc->pointarr[n]->isDoor == true && playerHasKey == true))
            {
                ava_loc = ava_loc->pointarr[n];
                if (ava_loc->isKey)
                {
                    playerHasKey = true;
                }
                return true;
            }
        }
    }

    return false;
}


float Maze::dist(Maze::Cell* c1, Maze::Cell* c2)//distance
{
    float x = c1->coor[0] - c2->coor[0];
    float y = c2->coor[1] - c2->coor[1];
    float d = sqrt(x*x + y*y);
    return d;
}

void Maze::getSurrond(int arr[3][3])//not needed
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            arr[i][j]= 0;
        }
    }
    arr[1][1] = 1;
    if (ava_loc->pointarr[0] != nullptr)
    {
        arr[0][1] = 1;
    }
    if (ava_loc->pointarr[1] != nullptr)
    {
        arr[1][2] = 1;
    }
    if (ava_loc->pointarr[2] != nullptr)
    {
        arr[2][1] = 1;
    }
    if (ava_loc->pointarr[3] != nullptr)
    {
        arr[0][1] = 1;
    }
}

void Maze::giveMazeDoors()//gives the maze doors, basically creates a box around the exit
{
    int n;
    for (int i = 10; i<15; i++)
    {
        n = 0;
        for (int k = 0; k<4; k++)
        {
            if (grid[i][10].pointarr[k] != nullptr){n++;}
        }
        if (((grid[i][10].pointarr[2] == nullptr || grid[i][10].pointarr[3] == nullptr)&&n != 1) || n >=3)
        {
            grid[i][10].isDoor = true;
        }
        n = 0;
        for (int k = 0; k<4; k++)
        {
            if (grid[10][i].pointarr[k] != nullptr){n++;}
        }
        if (((grid[10][i].pointarr[0] == nullptr || grid[10][i].pointarr[1] == nullptr)&&n != 1) || n>=3)
        {
            grid[10][i].isDoor = true;
        }
    }
}

void Maze::makeMazeInteresting()//gives doors and keys
{
    int n;
    for (int i = 10; i<15; i++)
    {
        n = 0;
        for (int k = 0; k<4; k++)
        {
            if (grid[i][10].pointarr[k] != nullptr){n++;}
        }
        if (((grid[i][10].pointarr[2] == nullptr || grid[i][10].pointarr[3] == nullptr)&&n != 1) || n >=3)
        {
            grid[i][10].isDoor = true;
        }
        n = 0;
        for (int k = 0; k<4; k++)
        {
            if (grid[10][i].pointarr[k] != nullptr){n++;}
        }
        if (((grid[10][i].pointarr[0] == nullptr || grid[10][i].pointarr[1] == nullptr)&&n != 1) || n>=3)
        {
            grid[10][i].isDoor = true;
        }
    }
    int arr[] = {0,0};
    depthFirstSerach(arr, 25, &placeKey);//goes through maze looking for a good place to put a key
    Cell* cellptr = nullptr;
    float furthest = -1.f;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            if (grid[i][j].isKey)
            {
                grid[i][j].isKey = false;
                if (dist(ava_loc, &grid[i][j])>=furthest)//basically finds the farthest place to put a key
                {
                    furthest = dist(ava_loc, &grid[i][j]);
                    cellptr = &grid[i][j];
                }
            }
        }
    }
    cellptr->isKey = true;//only the farthest place gets the key
}

void Maze::depthFirstSerach(int coor[], int limit, void (Maze::*func)(int[]))//depth first search
{
    int n = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            grid[i][j].visit = false;
        }
    }
    recursiveSearch(coor, 0, limit, func);
}

bool Maze::recursiveSearch(int coor[], int current, int limit, void (Maze::*func)(int[]))//actual recursive function to go through the maze
{//Very short code, but extremely ineffecient, like its incredibaly slow
    if (current == limit)//only goes a certain distance through the maze
    {
        (this->*func)(coor);
        return true;
    }
    grid[coor[0]][coor[1]];
    for (int k = 0; k<4; k++)
    {
        if (grid[coor[0]][coor[1]].pointarr[k] != nullptr && grid[coor[0]][coor[1]].pointarr[k]->visit == false)
        {
            if (recursiveSearch(grid[coor[0]][coor[1]].pointarr[k]->coor, current+1, limit, func))
            {
                return false;
            }
        }
    }
    return false;
}

void Maze::placeKey(int coor[])//puts a key
{
    grid[coor[0]][coor[1]].isKey = true;
}

Maze::~Maze()
{
    //dtor
}
