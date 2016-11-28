#include <string>
#include <stdio.h>
#include "AutomatedParkingStructure.h"
#include "Terminal.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

Terminal::Terminal(AutomatedParkingStructure tAps)
{
    aps = tAps;
    currentCustomer = null;
    currentVehicle = null;
}

Ticket Terminal::StoreCurrentVehicle()
{
    bool canBeStored = CanBeStored(vehicle);
    int availableSpaces = aps.GetAvailableSpaces();

    if(!canBeStored)
    {
        printf("Vehicle is too large and cannot be stored!\n");
    }
    else if(availableSpaces == 0)
    {
        printf("There are currently no spaces to store the vehicle in!\n");
    }
    else
    {
        return aps.StoreVehicle(currentCustomer, vehicle);
    }
    throw;
}

Vehicle Terminal::RetrieveVehicle(Ticket ticket)
{
    bool doNamesMatch = IsCorrectTicket(currentCustomer, ticket);

    if(!doNamesMatch)
    {
        printf("Customer does not have correct ticket!\n");
    }
    else
    {
        return aps.RetrieveVehicle(ticket);
    }
    throw;
}

bool Terminal::CanBeStored(Vehicle vehicle)
{
    double vehicleWeight = vehicle.GetWeight();
    int vehicleWheels = vehicle.GetWheels();

    return vehicleWeight < 1000.0 && vehicleWheels == 4;
}

bool Terminal::IsCorrectTicket(Customer customer, Ticket ticket)
{
    string customerName = customer.GetName();
    string ticketName = ticket.GetCustomerName();
    return customerName.compare(ticketName) == 0;
}

bool Terminal::IsCorrectLicensePlate(string licensePlate, Vehicle vehicle)
{
    string vehicleLicensePlate = vehicle.GetLicensePlate();
    return vehicleLicensePlate.compare(licensePlate) == 0;
}