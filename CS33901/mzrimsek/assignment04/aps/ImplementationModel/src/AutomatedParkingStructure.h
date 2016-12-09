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
        int totalSpaces;
        int floors;
        int dimension;
        Vehicle*** storedVehicles;
        bool IsCorrectLicensePlate(string, Vehicle);
        void Print();
    public:
        AutomatedParkingStructure(int, int);
        void StoreVehicle(Vehicle*);
        Vehicle& RetrieveVehicle(Ticket);
        int GetTotalSpaces();
        int GetAvailableSpaces();
};

#endif