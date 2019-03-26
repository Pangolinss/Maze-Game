#ifndef SPECIES_H
#define SPECIES_H
#include"Graph.h"

class Species
{
    public:
        Species();
        void print();
        void createAlgorithm();
        void outputGenome();
        virtual ~Species();

    protected:

    private:
        Graph algorithm;
        LinkList<int*> genome[15];//the connections values are encoded in the genome. The first one is itself, the rest are connections
        int cell_types[15][3][3];
};

#endif // SPECIES_H
