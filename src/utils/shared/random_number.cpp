#include <cstdlib>
#include <ctime>

int seed_random_number(int range = 100000000)
{
    srand(time(NULL));
    return rand() % range;
}