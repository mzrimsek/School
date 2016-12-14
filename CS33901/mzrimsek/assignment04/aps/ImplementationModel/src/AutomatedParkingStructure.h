#ifndef AutomatedParkingStructure_H
#define AutomatedParkingStructure_H

#include <string>

using namespace std;

#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

using namespace std;

class AutomatedParkingStructure
{
    private:
        int availableSpaces;
        int floors;
        int dimension;
        Vehicle*** storedVehicles;
        void Print();
        void SetPivotColumns(int&, int&, int);
        Vehicle& GetEmptySpace();
        Vehicle& GetReservedSpace();
    public:
        AutomatedParkingStructure(int, int);
        void StoreVehicle(Vehicle*);
        Vehicle& RetrieveVehicle(Ticket);
        int GetAvailableSpaces();
};

#endif