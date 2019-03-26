#include"Species.h"
#include<time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Species species;
    species.createAlgorithm();
    species.outputGenome();
    return 0;
}
