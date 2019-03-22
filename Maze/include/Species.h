#ifndef SPECIES_H
#define SPECIES_H
#include"Graph.h"

class Species
{
    public:
        Species();
        virtual ~Species();
        void print();

    protected:

    private:
        Graph algorithm;
        int cell_types[15][3][3];
};

#endif // SPECIES_H
