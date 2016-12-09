#include "AutomatedParkingStructure.h"
#include "Terminal.h"
#include "Models/Vehicle.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "TestObjectGetter.h"
#include <string>
#include <iostream>

using namespace std;

TestObjectGetter* testObjectGetter = new TestObjectGetter();

void LoadVehicleAndCustomer(Terminal* terminal, string vehicleFile, string customerFile)
{
    Vehicle* vehicle = testObjectGetter->GetVehicle(vehicleFile);
    Customer* customer = testObjectGetter->GetCustomer(customerFile);
    terminal->SetCurrentVehicle(vehicle);
    terminal->SetCurrentCustomer(customer);
}

void TestAddAndRetrieveValidVehicleForNonMember()
{
    cout << "Testing adding and retrieving valid vehicle for non member" << "\n";
    cout << "----------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(2, 2);
    Terminal* terminal = new Terminal(aps);

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");

    int totalSpaces = aps->GetAvailableSpaces();
    Ticket ticket = terminal->StoreCurrentVehicle(10);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces-1)
    {
        cout << "Vehicle added!\n";
    }

    terminal->RetrieveVehicle(ticket);
    availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle retrieved!\n";
    }
}

void TestAddAndRetrieveValidVehicleForMember()
{
    cout << "Testing adding and retrieving valid vehicle for member" << "\n";
    cout << "------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 3);
    Terminal* terminal = new Terminal(aps);

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/memberCustomer.txt");
    
    int totalSpaces = aps->GetAvailableSpaces();
    Ticket ticket = terminal->StoreCurrentVehicle(10);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces-1)
    {
        cout << "Vehicle added!\n";
    }

    terminal->RetrieveVehicle(ticket);
    availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle retrieved!\n";
    }
}

void TestRejectInvalidVehicle()
{
    cout << "Testing adding and retrieving invalid vehicle" << "\n";
    cout << "---------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 2);
    Terminal* terminal = new Terminal(aps);

    LoadVehicleAndCustomer(terminal, "inputs/invalidVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    int totalSpaces = aps->GetAvailableSpaces();
    Ticket ticket = terminal->StoreCurrentVehicle(10);
    int availableSpaces = aps->GetAvailableSpaces();
    if(totalSpaces == availableSpaces)
    {
        cout << "Vehicle rejected!\n";
    }
}

void TestNoSpaceToStoreVehicle()
{
    cout << "Testing no space to store vehicle" << "\n";
    cout << "---------------------------------" << "\n";
    
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    int totalSpaces = aps->GetAvailableSpaces();
    Ticket ticket = terminal->StoreCurrentVehicle(10);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle rejected!\n";
    }
}

void TestUpgradeNonMemberToMember()
{
    cout << "Testing upgrade non member to member" << "\n";
    cout << "------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);
    Customer* customer = testObjectGetter->GetCustomer("inputs/nonMemberCustomer.txt");
    terminal->SetCurrentCustomer(customer);
    terminal->UpgradeToMember();
}

void TestNotUpgradeMember()
{
    cout << "Testing not upgrade member" << "\n";
    cout << "--------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);
    Customer* customer = testObjectGetter->GetCustomer("inputs/memberCustomer.txt");
    terminal->SetCurrentCustomer(customer);
    terminal->UpgradeToMember();
}

void TestAddAndRetrieveTwoValidVehicleForNonMember()
{
    cout << "Testing adding and retrieving two valid vehicle for non member" << "\n";
    cout << "--------------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(2, 2);
    Terminal* terminal = new Terminal(aps);

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");

    int totalSpaces = aps->GetAvailableSpaces();
    Ticket ticket1 = terminal->StoreCurrentVehicle(10);
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces-1)
    {
        cout << "Vehicle added!\n";
    }

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle2.txt", "inputs/nonMemberCustomer.txt");
    Ticket ticket2 = terminal->StoreCurrentVehicle(20);
    availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces-2)
    {
        cout << "Vehicle added!\n";
    }

    terminal->RetrieveVehicle(ticket2);
    availableSpaces = aps->GetAvailableSpaces();

    terminal->RetrieveVehicle(ticket1);
    availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == totalSpaces)
    {
        cout << "Vehicle retrieved!\n";
    }
}

int main()
{
    cout << "1.";
    TestAddAndRetrieveValidVehicleForNonMember();
    cout << "\n\n";
    
    cout << "2.";
    TestAddAndRetrieveValidVehicleForMember();
    cout << "\n\n";
    
    cout << "3.";
    TestRejectInvalidVehicle();
    cout << "\n\n";
    
    cout << "4.";
    TestNoSpaceToStoreVehicle();
    cout << "\n\n";
    
    cout << "5.";
    TestUpgradeNonMemberToMember();
    cout << "\n\n";
    
    cout << "6.";
    TestNotUpgradeMember();
    cout << "\n\n";

    cout << "7.";
    TestAddAndRetrieveTwoValidVehicleForNonMember();
    cout << "\n\n";

    return 0;
}