#ifndef MAZESOLVER_H
#define MAZESOLVER_H
#include"Maze.h"
#include<conio.h>
#define RIGHT 0//what each number means
#define LEFT 1
#define DOWN 2
#define UP 3

class MazeSolver
{
    public:
        MazeSolver();
        MazeSolver(Maze*);
        virtual ~MazeSolver();
        void testSpecies(int);
        int getMovement(Node);
        void solveMaze();//my maze solver algorithm
        void solveMaze2();//algorithm because mine wasn't "stack-y" enough
        void solveMaze3();//algorithm with doors
        void solveMazeWrapper();//actual algorithm
        int generateDirection();
        void backTrack(int&);//backtrack funciton


    private:
        int inverse(int);//cals inverse

        Maze* maze;
        Stack<int> moves;
        Stack<int> back_moves;

};

bool compareArr(int[3][3], int[3][3]);
bool compareArr(int**, int[3][3]);

#endif // MAZESOLVER_H
