#ifndef Terminal_H
#define Terminal_H

#include <string>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

class Terminal
{
    private:
        AutomatedParkingStructure aps;
        Customer currentCustomer;
        Vehcile currentVehicle;
    public:
        Terminal(AutomatedParkingStructure);
        Ticket StoreCurrentVehicle();
        Vehicle RetrieveVehicle(Ticket);
        void SetCurrentCustomer(Customer);
        void SetCurrentVehicle(Vehicle);
}

#endif