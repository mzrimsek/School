#ifndef Terminal_H
#define Terminal_H

#include <string>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

using namespace std;

class Terminal
{
    private:
        AutomatedParkingStructure* aps;
        Customer* currentCustomer;
        Vehicle* currentVehicle;
        bool CanBeStored(Vehicle*);
        bool IsCorrectTicket(Customer*, Ticket);
        bool IsCorrectLicensePlate(string, Vehicle);
    public:
        Terminal(AutomatedParkingStructure*);
        Ticket& StoreCurrentVehicle();
        Vehicle& RetrieveVehicle(Ticket);
        void SetCurrentCustomer(Customer*);
        void SetCurrentVehicle(Vehicle*);
};

#endif