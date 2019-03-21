#ifndef SPECIES_H
#define SPECIES_H
#include"Graph.h"

class Species
{
    public:
        Species();
        virtual ~Species();

    protected:

    private:
        Graph algorithm;
        char cell_types[15][3][3];
};

#endif // SPECIES_H
