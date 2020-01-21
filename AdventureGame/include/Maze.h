#ifndef MAZE_H
#define MAZE_H
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<time.h>
#include"Stack.h"

const int SIZE = 15;
//a maze
class MazeSolver;
class Maze
{
    public:
        struct Cell//a cell is a 3x3 box, a maze is made by overlapping cells
        {
            struct Crossroad//checks if a cell is a crossroad, and how many marks it has
            {
                bool isCross;
                int mark[4];
            };
            Cell* pointarr[4];//poitns in 4 directions, 4 other cells
            Crossroad cross;
            bool visit; //used in building, also in Mr Maloley's maze solver
            bool isDoor;// door cell
            bool isKey;//if cell has a key
            int coor[2];//value of its position in an array
            Cell()
            {
                pointarr[0] = nullptr; //positive 2nd coor
                pointarr[1] = nullptr; //negative 2nd coor
                pointarr[2] = nullptr; //positive 1st coor
                pointarr[3] = nullptr; //negative 1st coor
            }
        };
        Maze();
        void generateMaze();//makes maze
        void buildMaze(int[]);//actually recursively makes the maze
        void makeMazeArr(int[2*SIZE+1][2*SIZE+1]);//turns the maze into an array
        void giveMazeDoors();//adds doors
        void makeMazeInteresting();//adds doors and a key
        void depthFirstSerach(int[], int, void(Maze::* func)(int[]));//a recursive algorithm to add kets
        bool recursiveSearch(int[], int, int, void(Maze::* func)(int[]));//the actual recursive algorithm, also does something
        void placeKey(int[]);//places a key
        void print();//prints maze
        void shuffle(int[][2], int);//shuffles an array
        void solveMaze();//nothing
        bool checkMove(int);//check move for my first solver
        bool checkMove2(int);//checks move for my second solver
        bool checkMove3(int);//checks move for my third solver (works with doors and keys)
        float dist(Cell*, Cell*);//calcs distance between cells
        void getSurrond(int[3][3]);//not used
        virtual ~Maze();
        friend class MazeSolver;
    private:
        Cell grid[SIZE][SIZE];//an array of linked cells, kind of like a 2d linked list imposed on an array
        Cell* ava_loc;//location of you
        int dir;//direction
        Cell* finish;//location of end
        bool playerHasKey;//if has key
};

#endif // MAZE_H
