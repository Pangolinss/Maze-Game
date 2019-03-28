#ifndef MAZESOLVER_H
#define MAZESOLVER_H
#include"Species.h"


class MazeSolver
{
    public:
        MazeSolver();
        virtual ~MazeSolver();

    protected:

    private:
        Graph* genetics;
        Stack move_list;
        int direction;

};

#endif // MAZESOLVER_H
