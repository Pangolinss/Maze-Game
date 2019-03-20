#include"Maze.h"
using namespace std;

int main()
{
    srand(time(NULL));
    Maze maze;
    maze.generateMaze();
    maze.print();
    return 0;
}
