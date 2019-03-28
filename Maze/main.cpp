#include"Species.h"
#include<time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Species father;
    Species mother;
    Species child;
    father.createAlgorithm();
    mother.createAlgorithm();
    mother.meiosis(father, child);

    return 0;
}
