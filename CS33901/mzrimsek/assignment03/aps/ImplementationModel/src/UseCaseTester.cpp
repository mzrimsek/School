#include "Terminal.h"

int main()
{
    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* loadingStation1 = new Terminal(aps);

    return 0;
}