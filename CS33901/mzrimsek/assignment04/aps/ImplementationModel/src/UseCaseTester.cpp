#include "Terminal.h"
#include "Models/Vehicle.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "TestObjectGetter.h"
#include <string>
#include <iostream>

using namespace std;

TestObjectGetter* testObjectGetter = new TestObjectGetter();

void loadVehicleAndCustomer(Terminal* terminal, string vehicleFile, string customerFile)
{
    Vehicle* vehicle = testObjectGetter->GetVehicle(vehicleFile);
    Customer* customer = testObjectGetter->GetCustomer(customerFile);
    terminal->SetCurrentVehicle(vehicle);
    terminal->SetCurrentCustomer(customer);
}

void testAddAndRetrieveValidVehicle()
{
    cout << "Testing adding and retrieving valid vehicle" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    Ticket ticket = terminal->StoreCurrentVehicle(0);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces-1)
    {
        cout << "Vehicle added!" << "\n";
    }

    terminal->RetrieveVehicle(ticket);
    availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle retrieved!" << "\n";
    }
}

void testRejectInvalidVehicle()
{
    cout << "Testing adding and retrieving invalid vehicle" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/invalidVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    terminal->StoreCurrentVehicle(0);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle correctly rejected!" << "\n";
    }
}

int main()
{
    testAddAndRetrieveValidVehicle();
    cout << "\n";
    testRejectInvalidVehicle();

    return 0;
}