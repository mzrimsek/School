#ifndef AutomatedParkingStructure_H
#define AutomatedParkingStructure_H

#include <string>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

class AutomatedParkingStructure
{
    private:
        int totalSpaces;
        vector<Vehicle> storedVehicles;
    public:
        AutomatedParkingStructure(int);
        Ticket StoreVehicle(Customer, Vehicle);
        Vehicle RetrieveVehicle(Customer, Ticket);
        int GetTotalSpaces();
        int GetAvailableSpaces();
}

#endif