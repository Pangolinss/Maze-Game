#ifndef MAZE_H
#define MAZE_H
#define SIZE 15
#include<iostream>
#include<cstdlib>
#include<time.h>
#include"Stack.h"


class Maze
{
    public:
        Maze();
        void generateMaze();
        void buildMaze(int[]);
        void print();
        void shuffle(int[][2], int);
        virtual ~Maze();

    private:
        struct Cell
        {
            Cell* pointarr[4];
            bool visit;

            Cell()
            {
                pointarr[0] = nullptr;
                pointarr[1] = nullptr;
                pointarr[2] = nullptr;
                pointarr[3] = nullptr;
                visit = false;
            }
        };
        Cell grid[SIZE][SIZE];
};

#endif // MAZE_H
