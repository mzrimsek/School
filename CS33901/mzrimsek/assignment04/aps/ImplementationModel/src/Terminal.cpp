#include <string>
#include <stdio.h>
#include "AutomatedParkingStructure.h"
#include "Terminal.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

Terminal::Terminal(AutomatedParkingStructure* tAps)
{
    aps = tAps;
}

Ticket& Terminal::StoreCurrentVehicle(int timeToStore)
{
    bool canBeStored = CanBeStored(currentVehicle);
    int availableSpaces = aps->GetAvailableSpaces();

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
        aps->StoreVehicle(currentCustomer, currentVehicle);
        string customerName = currentCustomer->GetName();
        string licensePlate = currentVehicle->GetLicensePlate();
        return *(new Ticket(customerName, licensePlate, timeToStore));
    }
    return *(new Ticket("", "", 0));
}

Vehicle& Terminal::RetrieveVehicle(Ticket ticket)
{
    bool doNamesMatch = IsCorrectTicket(currentCustomer, ticket);

    if(!doNamesMatch)
    {
        printf("Customer does not have correct ticket!\n");
        return *(new Vehicle("", "", "", 0, 0, 0));
    }
    
    if(currentCustomer->GetIsMember())
    {
        printf("Customer is a member - not billed!\n");
    }
    else
    {
        int timeStored = ticket.GetTimeToStore();
        double costForStorage = GetCostForStorage(timeStored);
        printf("Customer is not a member - %.2f billed for %d hours!\n", costForStorage, timeStored);
    }
    return aps->RetrieveVehicle(ticket);
}

bool Terminal::CanBeStored(Vehicle* vehicle)
{
    double vehicleWeight = vehicle->GetWeight();
    int vehicleWheels = vehicle->GetWheels();

    return vehicleWeight < 1000.0 && vehicleWheels == 4;
}

bool Terminal::IsCorrectTicket(Customer* customer, Ticket ticket)
{
    string customerName = customer->GetName();
    string ticketName = ticket.GetCustomerName();
    return customerName.compare(ticketName) == 0;
}

bool Terminal::IsCorrectLicensePlate(string licensePlate, Vehicle vehicle)
{
    string vehicleLicensePlate = vehicle.GetLicensePlate();
    return vehicleLicensePlate.compare(licensePlate) == 0;
}

double Terminal::GetCostForStorage(int timeStored)
{
    return timeStored * 2.38;
}

void Terminal::SetCurrentCustomer(Customer* customer)
{
    currentCustomer = customer;
}

void Terminal::SetCurrentVehicle(Vehicle* vehicle)
{
    currentVehicle = vehicle;
}

void Terminal::UpgradeToMember()
{
    if(currentCustomer->GetIsMember())
    {
        printf("Customer is already member!\n");
    }
    else
    {
        currentCustomer->SetIsMember(true);
        printf("Customer is now a member and has been billed $20 for first month's subscription!\n");
    }
}