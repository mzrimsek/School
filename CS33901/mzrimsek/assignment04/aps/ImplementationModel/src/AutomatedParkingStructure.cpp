#include <string>
#include <iostream>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

AutomatedParkingStructure::AutomatedParkingStructure(int floors, int dimension)
{
    totalSpaces = floors*dimension*dimension;
    storedVehicles = new Vehicle**[floors];

    for(int floor = 0; floor < floors; floor++)
    {
        storedVehicles[floor] = new Vehicle*[dimension+1];
        for(int row = 0; row < dimension+1; row++)
        {
            storedVehicles[floor][row] = new Vehicle[dimension];
            for(int column = 0; column < dimension; column++)
            {
                storedVehicles[floor][row][column] = *(new Vehicle("", "", "", 0, 0, 0));
            }
        } 
    }

    for(int floor = 0; floor < floors; floor++)
    {
        for(int column = 0; column < dimension; column++)
        {
            storedVehicles[floor][dimension][column] = *(new Vehicle("RES", "", "", 0, 0, 0));
        }
    }

    Print(floors, dimension);
}

void AutomatedParkingStructure::StoreVehicle(Vehicle* vehicle)
{
    
}

Vehicle& AutomatedParkingStructure::RetrieveVehicle(Ticket ticket)
{
    string vehicleLicensePlate = ticket.GetVehicleLicensePlate();
    
    printf("Vehicle not found!");
    return *(new Vehicle("", "", "", 0, 0, 0));
}

int AutomatedParkingStructure::GetTotalSpaces()
{
    return totalSpaces;
}

int AutomatedParkingStructure::GetAvailableSpaces()
{
    return totalSpaces;
}

bool AutomatedParkingStructure::IsCorrectLicensePlate(string licensePlate, Vehicle vehicle)
{
    string vehicleLicensePlate = vehicle.GetLicensePlate();
    return vehicleLicensePlate.compare(licensePlate) == 0;
}

void AutomatedParkingStructure::Print(int floors, int dimension)
{
    for(int floor = 0; floor < floors; floor++)
    {
        cout << "floor " << floor << "\n";
        for(int row = 0; row < dimension+1; row++)
        {
            for(int column = 0; column < dimension; column++)
            {
                cout << "[" << storedVehicles[floor][row][column].GetLicensePlate() << "]";
            }
            cout << "\n";
        }
    }
}