#include <string>
#include <stdio.h>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

AutomatedParkingStructure::AutomatedParkingStructure(int tTotalSpaces)
{
    totalSpaces = tTotalSpaces;
    storedVehicles.reserve(totalSpaces);
}

Ticket& AutomatedParkingStructure::StoreVehicle(Customer* customer, Vehicle* vehicle)
{
    Vehicle vehicleToStore = *vehicle;
    storedVehicles.push_back(vehicleToStore);
    string customerName = customer->GetName();
    string licensePlate = vehicleToStore.GetLicensePlate();
    return *(new Ticket(customerName, licensePlate));
}

Vehicle& AutomatedParkingStructure::RetrieveVehicle(Ticket ticket)
{
    string vehicleLicensePlate = ticket.GetVehicleLicensePlate();
    for(int i = 0; i < storedVehicles.size(); i++)
    {
        Vehicle currentVehicle = storedVehicles[i];
        bool doLicensePlatesMatch = IsCorrectLicensePlate(vehicleLicensePlate, currentVehicle);

        if(doLicensePlatesMatch)
        {
            storedVehicles.erase(storedVehicles.begin()+i);
            return currentVehicle;
        }
    }
    printf("Vehicle not found!");
    return *(new Vehicle("", "", "", 0, 0, 0));
}

int AutomatedParkingStructure::GetTotalSpaces()
{
    return totalSpaces;
}

int AutomatedParkingStructure::GetAvailableSpaces()
{
    return totalSpaces - storedVehicles.size();
}

bool AutomatedParkingStructure::IsCorrectLicensePlate(string licensePlate, Vehicle vehicle)
{
    string vehicleLicensePlate = vehicle.GetLicensePlate();
    return vehicleLicensePlate.compare(licensePlate) == 0;
}