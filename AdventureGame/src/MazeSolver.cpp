#include "MazeSolver.h"

//0 right
//1 left
//2 down
//3 up

MazeSolver::MazeSolver()
{
    //ctor
}

MazeSolver::MazeSolver(Maze* _maze)
{
    maze = _maze;
}

MazeSolver::~MazeSolver()
{
    //dtor
}

void MazeSolver::solveMaze()
{
    //Tremaux Algorithm
    //This algorithm is essentially a normal maze solver thats slightly more space effecient!
    //Essentially, you can think of a maze as a graph of intersection, if an intersection is connected, there is a line between them
    //Traversing through the maze is just traveling through the graph
    //So you only need to mark your intersections, and which way you went on the intersection
    //If a direction has 2 marks dont go there
    bool c;
    bool first_move = true;
    Maze::Cell* prev = nullptr;
    int move_dir;
    int last_move;
    moves.push(0);
    maze->ava_loc->cross.isCross = true;
    while (true)
    {
        int paths[4] = {0,0,0,0};
        if (maze->ava_loc == maze->finish)
        {
            return;
        }
        for (int k = 0; k<4; k++)
        {
            if (maze->ava_loc->pointarr[k] != nullptr)
            {
                paths[k] = 1;//checks if there is a pathway
            }
        }
        if (paths[0]+paths[1]+paths[2]+paths[3] == 2 || first_move==true)//if a pathway is a hallway (2 directions) just continue moving away from where you were
        {
            for (int k = 0; k<4; k++)
            {
                if (paths[k] != 0 && maze->ava_loc->pointarr[k] != prev)
                {
                    move_dir = k;
                }
            }
        }
        else if (paths[0]+paths[1]+paths[2]+paths[3] > 2)//if its an intersection
        {
            maze->ava_loc->cross.isCross = true;
            maze->ava_loc->cross.mark[inverse(last_move)]++;
            if (paths[2] == 1 && maze->ava_loc->cross.mark[2] == 0 && maze->ava_loc->pointarr[2] != prev)         {move_dir = 2;}//move in set directions
            else if (paths[0] == 1 && maze->ava_loc->cross.mark[0] == 0 && maze->ava_loc->pointarr[0] != prev)    {move_dir = 0;}
            else if (paths[1] == 1 && maze->ava_loc->cross.mark[1] == 0 && maze->ava_loc->pointarr[1] != prev)    {move_dir = 1;}
            else if (paths[3] == 1 && maze->ava_loc->cross.mark[3] == 0 && maze->ava_loc->pointarr[3] != prev)    {move_dir = 3;}
            else if ((maze->ava_loc->cross.mark[0]<2)&&(maze->ava_loc->cross.mark[1]<2)&&(maze->ava_loc->cross.mark[2]<2)&&(maze->ava_loc->cross.mark[3]<2))//if each one has a mark go back
            {
                move_dir = inverse(last_move);
            }
            else
            {
                if (paths[2] == 1 && maze->ava_loc->cross.mark[2] < 2 && maze->ava_loc->pointarr[2] != prev)      {move_dir = 2;}//if they all have marks pick the one with the least
                else if (paths[0] == 1 && maze->ava_loc->cross.mark[0] < 2 && maze->ava_loc->pointarr[0] != prev) {move_dir = 0;}
                else if (paths[1] == 1 && maze->ava_loc->cross.mark[1] < 2 && maze->ava_loc->pointarr[1] != prev) {move_dir = 1;}
                else if (paths[3] == 1 && maze->ava_loc->cross.mark[3] < 2 && maze->ava_loc->pointarr[3] != prev) {move_dir = 3;}
            }//never go through a path with 2 marks
            maze->ava_loc->cross.mark[move_dir]++;
        }
        moves.push(move_dir);
        system("PAUSE");

        if (paths[0]+paths[1]+paths[2]+paths[3] == 1 && first_move == false)//deadend
        {
            while (maze->ava_loc->cross.isCross != true)
            {
                prev = maze->ava_loc;
                backTrack(last_move);
                system("CLS");
                maze->print();
            }

        }
        else
        {
            prev = maze->ava_loc;
            maze->checkMove(moves.peek());
            last_move = move_dir;
            system("CLS");
            maze->print();

        }
        first_move = false;
    }
    return;
}

void MazeSolver::solveMaze2()//Algorithm that uses more stacks
{
    Element<int>* ele;
    bool inBack = true;
    int k;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            maze->grid[i][j].visit = false;
        }
    }
    while (true)
    {
        if (maze->ava_loc == maze->finish)
        {
            return;
        }
        maze->ava_loc->visit = true;
        inBack = true;
        moves.push(3);//pushes all moves
        moves.push(1);
        moves.push(0);
        moves.push(2);
        k = 0;
        for (int i = 0; i<4; i++)
        {
            ele = moves.pop();
            if (maze->checkMove2(ele->getValue()))//pops off moves and checks them, if a valid move is found disables backtracking
            {
                back_moves.push(ele->getValue());
                inBack = false;
                i = 4;
            }
        }
        if (inBack)
        {
            ele = back_moves.pop();//backtracks if you are in the backtrack mode
            maze->checkMove(inverse(ele->getValue()));
        }
        maze->print();
        system("PAUSE");
        system("CLS");
    }
}

void MazeSolver::solveMaze3()//same as solvemaze2 but with doors
{
    Element<int>* ele;
    bool inBack = true;
    int k;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            maze->grid[i][j].visit = false;
        }
    }
    if (!maze->playerHasKey)
    {
        while (true)
        {
            if (maze->playerHasKey)
            {
                return;
            }
            maze->ava_loc->visit = true;
            inBack = true;
            moves.push(3);
            moves.push(1);
            moves.push(0);
            moves.push(2);
            k = 0;
            for (int i = 0; i<4; i++)
            {
                ele = moves.pop();
                if (maze->checkMove3(ele->getValue()))
                {
                    back_moves.push(ele->getValue());
                    inBack = false;
                    i = 4;
                }
            }
            if (inBack)
            {
                ele = back_moves.pop();
                maze->checkMove(inverse(ele->getValue()));
            }
            maze->print();
            system("PAUSE");
            system("CLS");
        }
    }
    else
    {
        while (true)
        {
            if (maze->ava_loc == maze->finish)
            {
                return;
            }
            maze->ava_loc->visit = true;
            inBack = true;
            moves.push(3);
            moves.push(1);
            moves.push(0);
            moves.push(2);
            k = 0;
            for (int i = 0; i<4; i++)
            {
                ele = moves.pop();
                if (maze->checkMove3(ele->getValue()))
                {
                    back_moves.push(ele->getValue());
                    inBack = false;
                    i = 4;
                }
            }
            if (inBack)
            {
                ele = back_moves.pop();
                maze->checkMove(inverse(ele->getValue()));
            }
            maze->print();
            system("PAUSE");
            system("CLS");
        }
    }
}

void MazeSolver::solveMazeWrapper()
{
    solveMaze3();//finds key
    solveMaze3();//solves maze
    //If only pathways to the exit had doors on them, a short cut would be to save the moves needed to get to a door, but my generation
    //does not do this, so the most effecient method is to just resolve the maze
}

void MazeSolver::backTrack(int& last_move)//goes back by taking the inverse of each move
{
    Element<int>* ele;
    ele = moves.pop();
    maze->checkMove(inverse(ele->getValue()));
    last_move = inverse(ele->getValue());
    delete ele;
}

int MazeSolver::inverse(int n)//calculates the inverse of a move
{
    switch (n)
    {
        case 0: return 1;
        case 1: return 0;
        case 2: return 3;
        case 3: return 2;
        default:
            system("CLS");
            std::cout<<"Invalid inverse"<<std::endl;
            return -1;
    }
}

bool compareArr(int a1[3][3], int a2[3][3])
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (a1[i][j] != a2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool compareArr(int** a1, int a2[3][3])
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (a1[i][j] != a2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
