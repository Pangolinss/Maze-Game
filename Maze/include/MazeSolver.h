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
        Species population[50];

};

#endif // MAZESOLVER_H
