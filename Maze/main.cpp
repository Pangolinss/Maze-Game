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
    child = mother.meiosis(father);

    return 0;
}
