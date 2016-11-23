#include <vector>
#include "Models/Vehicle.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"

using namespace std;

class AutomatedParkingStructure
{
    private:
        int totalSpaces;
        int availableSpaces;
        vector<Vehicle> storedVehicles;
    public:
        AutomatedParkingStructure(int, int);
        Ticket StoreVehicle(Customer, Vehicle);
        Vehicle RetrieveVehicle(Customer, Ticket);
}

AutomatedParkingStructure::AutomatedParkingStructure(int tTotalSpaces, int tAvailableSpaces)
{
    totalSpaces = tTotalSpaces;
    availableSpaces = tAvailableSpaces;
    storedVehicles(vector<Vehicle>(totalSpaces));
}

Ticket AutomatedParkingStructure::StoreVehicle(Customer customer, Vehicle vehicle)
{
    bool canBeStored = CanBeStored(vehicle);
    
    if(canBeStored && availableSpaces != 0)
    {
        int vehiclePosition = GetNextValidVehiclePosition(vehicle);
        storedVehicles[vehiclePosition] = vehicle;
        
        string customerName = customer.GetName();
        return new Ticket(customerName, vehiclePosition);
    }
    return null;
}

Vehicle AutomatedParkingStructure::RetrieveVehicle(Customer customer, Ticket ticket)
{
    string customerName = customer.GetName();
    string ticketName = ticket.GetCustomerName();

    if(customerName.compare(ticketName) == 0)
    {
        int vehiclePosition = ticket.GetVehiclePosition();
        return storedVehicles[vehiclePosition];
    }
    return null;
}

bool CanBeStored(Vehicle vehicle)
{
    double vehicleWeight = vehicle.GetWeight();
    int vehicleWheels = vehicle.GetWheels();

    return vehicleWeight < 1000.0 && vehicleWheels == 4;
}

int GetNextValidVehiclePosition(Vehicle vehicle)
{
    int vehiclePosition = 0;
    int iteration = 0;
    while(storedVehicles[vehiclePosition] != null)
    {
        vehiclePosition = HashVehicle(vehicle, iteration);
        iteration++;
    }
    return vehiclePosition;
}

int HashVehicle(Vehicle vehicle, int iteration)
{
    string licensePlate = vehicle.GetLicensePlate();
    int hash = 0;
    for(int i = 0; i < licensePlate.size; i++)
    {
        hash += licensePlate[i] * (i * iteration);
    }
    return hash % totalSpaces;
}