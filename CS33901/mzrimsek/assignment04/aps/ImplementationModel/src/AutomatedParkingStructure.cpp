#include <string>
#include <iostream>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

const string EMPTY = " EMPTY ";
const string RESERVED = "RESERVE";

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
                storedVehicles[floor][row][column] = *(new Vehicle(EMPTY, "", "", 0, 0, 0));
            }
        } 
    }

    for(int floor = 0; floor < floors; floor++)
    {
        for(int column = 0; column < dimension; column++)
        {
            storedVehicles[floor][dimension][column] = *(new Vehicle(RESERVED, "", "", 0, 0, 0));
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
                if(spot.GetLicensePlate().compare(EMPTY) == 0 && !spotFound)
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
    int foundFloor = 0;
    int foundRow = 0;
    int foundColumn = 0;

    bool spotFound = false;
    for(int floor = 0; floor < floors && !spotFound; floor++)
    {
        for(int column = dimension-1; column >= 0 && !spotFound; column--)
        {
            for(int row = 0; row < dimension && !spotFound; row++)
            {
                Vehicle spot = storedVehicles[floor][row][column];
                if(spot.GetLicensePlate().compare(vehicleLicensePlate) == 0)
                {
                    foundFloor = floor;
                    foundRow = row;
                    foundColumn = column;
                    spotFound = true;
                }
            }
        }
    }

    if(spotFound)
    {
        int leftColumn = 0;        
        int rightColumn = 0;

        if(foundColumn == 0)
        {
            leftColumn = foundColumn;
            rightColumn = foundColumn+1;
        }
        else
        {
            leftColumn = foundColumn-1;
            rightColumn = foundColumn;
        }
        
        while(true)
        {
            for(int row = 0; row < dimension; row++)
            {
                storedVehicles[foundFloor][row+1][leftColumn] = storedVehicles[foundFloor][row][leftColumn];
                storedVehicles[foundFloor][row][leftColumn] = *(new Vehicle(EMPTY, "", "", 0, 0, 0));
            }

            storedVehicles[foundFloor][0][leftColumn] = storedVehicles[foundFloor][0][rightColumn];
            storedVehicles[foundFloor][0][rightColumn] = *(new Vehicle(EMPTY, "", "", 0, 0, 0));

            for(int row = dimension-1; row > 0; row--)
            {
                storedVehicles[foundFloor][row-1][rightColumn] = storedVehicles[foundFloor][row][rightColumn];
                storedVehicles[foundFloor][row][rightColumn] = *(new Vehicle(EMPTY, "", "", 0, 0, 0));
            }

            Vehicle spot = storedVehicles[foundFloor][dimension][leftColumn];
            if(spot.GetLicensePlate().compare(vehicleLicensePlate) == 0)
            {
                storedVehicles[foundFloor][dimension][leftColumn] = *(new Vehicle(RESERVED, "", "", 0, 0, 0));
                availableSpaces++;
                Print();
                return spot;
            }
            else
            {
                storedVehicles[foundFloor][dimension-1][rightColumn] = spot;
                storedVehicles[foundFloor][dimension][leftColumn] = *(new Vehicle(RESERVED, "", "", 0, 0, 0));
                Print();  
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

void AutomatedParkingStructure::Print()
{
    for(int floor = 0; floor < floors; floor++)
    {
        cout << "floor " << floor+1 << "\n";
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