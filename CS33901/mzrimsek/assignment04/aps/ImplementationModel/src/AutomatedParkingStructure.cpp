#include <string>
#include <iostream>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

AutomatedParkingStructure::AutomatedParkingStructure(int tFloors, int tDimension)
{
    floors = tFloors;
    dimension = tDimension;

    availableSpaces = floors*dimension*dimension;
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
}

void AutomatedParkingStructure::StoreVehicle(Vehicle* vehicle)
{
    bool spotFound = false;
    for(int floor = 0; floor < floors && !spotFound; floor++)
    {
        for(int column = dimension-1; column >= 0 && !spotFound; column--)
        {
            for(int row = 0; row < dimension && !spotFound; row++)
            {
                Vehicle spot = storedVehicles[floor][row][column];
                if(spot.GetLicensePlate().compare("") == 0 && !spotFound)
                {
                    storedVehicles[floor][row][column] = *vehicle;
                    availableSpaces--;
                    spotFound = true;
                    Print();
                }
            }
        }
    }
}

Vehicle& AutomatedParkingStructure::RetrieveVehicle(Ticket ticket)
{
    string vehicleLicensePlate = ticket.GetVehicleLicensePlate();
    for(int floor = 0; floor < floors; floor++)
    {
        for(int column = dimension-1; column >= 0; column--)
        {
            for(int row = 0; row < dimension; row++)
            {
                Vehicle spot = storedVehicles[floor][row][column];
                if(spot.GetLicensePlate().compare(vehicleLicensePlate) == 0)
                {
                    storedVehicles[floor][row][column] = *(new Vehicle("", "", "", 0, 0, 0));
                    availableSpaces++;
                    Print();
                }
                return spot;
            }
        }
    }
    printf("Vehicle not found!\n");
    return *(new Vehicle("", "", "", 0, 0, 0));
}

int AutomatedParkingStructure::GetAvailableSpaces()
{
    return availableSpaces;
}

bool AutomatedParkingStructure::IsCorrectLicensePlate(string licensePlate, Vehicle vehicle)
{
    string vehicleLicensePlate = vehicle.GetLicensePlate();
    return vehicleLicensePlate.compare(licensePlate) == 0;
}

void AutomatedParkingStructure::Print()
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