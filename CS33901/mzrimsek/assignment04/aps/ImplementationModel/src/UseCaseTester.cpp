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

Ticket StoreTestVehicle(Terminal* terminal, AutomatedParkingStructure* aps, int& availableSpaces)
{
    Ticket ticket = terminal->StoreCurrentVehicle(10);
    availableSpaces = aps->GetAvailableSpaces();
    return ticket;
}

void RetrieveTestVehicle(Terminal* terminal, AutomatedParkingStructure* aps, Ticket ticket, int& availableSpaces)
{
    terminal->RetrieveVehicle(ticket);
    availableSpaces = aps->GetAvailableSpaces();
}

bool AssertSpaces(int expectedSpaces, int actualSpaces)
{
    return expectedSpaces == actualSpaces;
}

bool TestAddAndRetrieveValidVehicleForNonMember()
{
    cout << "Testing adding and retrieving valid vehicle for non member" << "\n";
    cout << "----------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 3);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    Ticket ticket = StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicleWasStored = AssertSpaces(totalSpaces-1, availableSpaces);
    
    RetrieveTestVehicle(terminal, aps, ticket, availableSpaces);
    bool vehicleWasRetrieved = AssertSpaces(totalSpaces, availableSpaces);
    
    return vehicleWasStored && vehicleWasRetrieved;
}

bool TestAddAndRetrieveValidVehicleForMember()
{
    cout << "Testing adding and retrieving valid vehicle for member" << "\n";
    cout << "------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 3);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/memberCustomer.txt");
    
    Ticket ticket = StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicleWasStored = AssertSpaces(totalSpaces-1, availableSpaces);
    
    RetrieveTestVehicle(terminal, aps, ticket, availableSpaces);
    bool vehicleWasRetrieved = AssertSpaces(totalSpaces, availableSpaces);

    return vehicleWasStored && vehicleWasRetrieved;
}

bool TestRejectInvalidVehicle()
{
    cout << "Testing adding and retrieving invalid vehicle" << "\n";
    cout << "---------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 2);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    LoadVehicleAndCustomer(terminal, "inputs/invalidVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    StoreTestVehicle(terminal, aps, availableSpaces);
    return AssertSpaces(totalSpaces, availableSpaces);
}

bool TestNoSpaceToStoreVehicle()
{
    cout << "Testing no space to store vehicle" << "\n";
    cout << "---------------------------------" << "\n";
    
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    StoreTestVehicle(terminal, aps, availableSpaces);
    return AssertSpaces(totalSpaces, availableSpaces);
}

bool TestUpgradeNonMemberToMember()
{
    cout << "Testing upgrade non member to member" << "\n";
    cout << "------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);

    Customer* customer = testObjectGetter->GetCustomer("inputs/nonMemberCustomer.txt");
    terminal->SetCurrentCustomer(customer);

    bool beforeUpgrade = customer->GetIsMember();
    terminal->UpgradeToMember();
    bool afterUpgrade = customer->GetIsMember();

    return beforeUpgrade != afterUpgrade;
}

bool TestNotUpgradeMember()
{
    cout << "Testing not upgrade member" << "\n";
    cout << "--------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);

    Customer* customer = testObjectGetter->GetCustomer("inputs/memberCustomer.txt");
    terminal->SetCurrentCustomer(customer);

    bool beforeUpgrade = customer->GetIsMember();
    terminal->UpgradeToMember();
    bool afterUpgrade = customer->GetIsMember();

    return beforeUpgrade == afterUpgrade;
}

bool TestAddAndRetrieveTwoValidVehicleForNonMember()
{
    cout << "Testing adding and retrieving two valid vehicle for non member" << "\n";
    cout << "--------------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(2, 2);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");

    Ticket ticket1 = StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicle1WasStored = AssertSpaces(totalSpaces-1, availableSpaces);

    LoadVehicleAndCustomer(terminal, "inputs/validVehicle2.txt", "inputs/nonMemberCustomer.txt");
    Ticket ticket2 = StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicle2WasStored = AssertSpaces(totalSpaces-2, availableSpaces);

    RetrieveTestVehicle(terminal, aps, ticket2, availableSpaces);
    bool vehicle2WasRetrieved = AssertSpaces(totalSpaces-1, availableSpaces);

    RetrieveTestVehicle(terminal, aps, ticket1, availableSpaces);
    bool vehicle1WasRetrieved = AssertSpaces(totalSpaces, availableSpaces);

    return (vehicle1WasStored && vehicle2WasStored) && (vehicle2WasRetrieved && vehicle1WasRetrieved);
}

void PrintResults(bool testResults)
{
    if(testResults)
    {
        cout << "\nPASS" << endl;
    }
    else
    {
        cout << "\nFAIL" << endl;
    }

    cout << "\n\n";
}

int main()
{
    cout << "1.";
    bool results = TestAddAndRetrieveValidVehicleForNonMember();
    PrintResults(results);
    
    cout << "2.";
    results = TestAddAndRetrieveValidVehicleForMember();
    PrintResults(results);
    
    cout << "3.";
    results = TestRejectInvalidVehicle();
    PrintResults(results);
    
    cout << "4.";
    results = TestNoSpaceToStoreVehicle();
    PrintResults(results);
    
    cout << "5.";
    results = TestUpgradeNonMemberToMember();
    PrintResults(results);
    
    cout << "6.";
    results = TestNotUpgradeMember();
    PrintResults(results);

    cout << "7.";
    results = TestAddAndRetrieveTwoValidVehicleForNonMember();
    PrintResults(results);

    return 0;
}