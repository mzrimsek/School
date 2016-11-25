#include <string>
#include <vector>
#include "AutomatedParkingStructure.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "Models/Vehicle.h"

using namespace std;

class AutomatedParkingStructure
{
    private:
        int totalSpaces;
        vector<Vehicle> storedVehicles;
    public:
        AutomatedParkingStructure(int, int);
        Ticket StoreVehicle(Customer, Vehicle);
        Vehicle RetrieveVehicle(Customer, Ticket);
        int GetTotalSpaces();
        int GetAvailableSpaces();
}

AutomatedParkingStructure::AutomatedParkingStructure(int tTotalSpaces, int tAvailableSpaces)
{
    totalSpaces = tTotalSpaces;
    storedVehicles(vector<Vehicle>(0));
}

Ticket AutomatedParkingStructure::StoreVehicle(Customer customer, Vehicle vehicle)
{
    storedVehicles.push_back(vehicle);
    string customerName = customer.GetName();
    return new Ticket(customerName, vehiclePosition);
}

Vehicle AutomatedParkingStructure::RetrieveVehicle(Customer customer, Ticket ticket)
{
    string vehicleLicensePlate = ticket.GetVehicleLicensePlate();
    for(int i = 0; i < storedVehicles.size; i++)
    {
        Vehicle currentVehicle = storedVehicles[i];
        bool doLicensePlatesMatch = IsCorrectLicensePlate(vehicleLicensePlate, currentVehicle);

        if(doLicensePlatesMatch)
        {
            storedVehicles.erase(i);
            return currentVehicle;
        }
    }
    printf("Vehicle not found!");
    return null;
}

int AutomatedParkingStructure::GetTotalSpaces()
{
    return totalSpaces;
}

int AutomatedParkingStructure::GetAvailableSpaces()
{
    return totalSpaces - storedVehicles.size;
}

bool IsCorrectLicensePlate(string licensePlate, Vehicle vehicle)
{
    string vehicleLicensePlate = vehicle.GetLicensePlate();
    return vehicleLicensePlate.compare(licensePlate) == 0;
}