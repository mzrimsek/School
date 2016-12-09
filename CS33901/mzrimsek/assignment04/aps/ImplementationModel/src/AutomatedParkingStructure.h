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
        Vehicle*** storedVehicles;
        bool IsCorrectLicensePlate(string, Vehicle);
    public:
        AutomatedParkingStructure(int, int);
        void StoreVehicle(Vehicle*);
        Vehicle& RetrieveVehicle(Ticket);
        int GetTotalSpaces();
        int GetAvailableSpaces();
};

#endif