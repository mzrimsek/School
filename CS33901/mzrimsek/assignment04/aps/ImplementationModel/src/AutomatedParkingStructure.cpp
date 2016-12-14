#include <string>
#include <iostream>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

const string EMPTY = " EMPTY ";
const string RESERVED = "RESERVE";

Vehicle& AutomatedParkingStructure::GetEmptySpace()
{
    return *(new Vehicle(EMPTY, "", "", 0, 0, 0));
}

Vehicle& AutomatedParkingStructure::GetReservedSpace()
{
    return *(new Vehicle(RESERVED, "", "", 0, 0, 0));
}

void AutomatedParkingStructure::SetPivotColumns(int& leftColumn, int& rightColumn, int foundColumn)
{
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
}

void AutomatedParkingStructure::ShiftLeftColumn(int foundFloor, int leftColumn)
{
    for(int row = 0; row < dimension; row++)
    {
        storedVehicles[foundFloor][row+1][leftColumn] = storedVehicles[foundFloor][row][leftColumn];
        storedVehicles[foundFloor][row][leftColumn] = GetEmptySpace();
    }
}

void AutomatedParkingStructure::ShiftRightColumn(int foundFloor, int rightColumn)
{
    for(int row = dimension-1; row > 0; row--)
    {
        storedVehicles[foundFloor][row-1][rightColumn] = storedVehicles[foundFloor][row][rightColumn];
        storedVehicles[foundFloor][row][rightColumn] = GetEmptySpace();
    }
}

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
                if(row == dimension)
                {
                    storedVehicles[floor][dimension][column] = GetReservedSpace();
                }
                else
                {
                    storedVehicles[floor][row][column] = GetEmptySpace(); 
                }
            }
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
        SetPivotColumns(leftColumn, rightColumn, foundColumn);
        
        while(true)
        {
            ShiftLeftColumn(foundFloor, leftColumn);

            storedVehicles[foundFloor][0][leftColumn] = storedVehicles[foundFloor][0][rightColumn];
            storedVehicles[foundFloor][0][rightColumn] = GetEmptySpace();

            ShiftRightColumn(foundFloor, rightColumn);

            Vehicle spot = storedVehicles[foundFloor][dimension][leftColumn];
            if(spot.GetLicensePlate().compare(vehicleLicensePlate) == 0)
            {
                storedVehicles[foundFloor][dimension][leftColumn] = GetReservedSpace();
                availableSpaces++;
                Print();
                return spot;
            }
            else
            {
                storedVehicles[foundFloor][dimension-1][rightColumn] = spot;
                storedVehicles[foundFloor][dimension][leftColumn] = GetReservedSpace();
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