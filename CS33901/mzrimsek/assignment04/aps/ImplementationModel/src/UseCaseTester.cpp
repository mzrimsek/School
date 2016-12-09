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

void TestAddAndRetrieveValidVehicleForNonMember()
{
    cout << "Testing adding and retrieving valid vehicle for non member" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    Ticket ticket = terminal->StoreCurrentVehicle(10);
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

void TestAddAndRetrieveValidVehicleForMember()
{
    cout << "Testing adding and retrieving valid vehicle for member" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/memberCustomer.txt");
    
    Ticket ticket = terminal->StoreCurrentVehicle(10);
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

void TestRejectInvalidVehicle()
{
    cout << "Testing adding and retrieving invalid vehicle" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/invalidVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    terminal->StoreCurrentVehicle(10);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle correctly rejected!" << "\n";
    }
}

int main()
{
    TestAddAndRetrieveValidVehicleForNonMember();
    cout << "\n";
    TestAddAndRetrieveValidVehicleForMember();
    cout << "\n";
    TestRejectInvalidVehicle();

    return 0;
}