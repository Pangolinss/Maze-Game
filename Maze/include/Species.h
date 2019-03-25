#ifndef SPECIES_H
#define SPECIES_H
#include"Graph.h"

class Species
{
    public:
        Species();
        void print();
        void createAlgorithm();
        virtual ~Species();

    protected:

    private:
        Graph algorithm;
        int cell_types[15][3][3];
};

#endif // SPECIES_H
