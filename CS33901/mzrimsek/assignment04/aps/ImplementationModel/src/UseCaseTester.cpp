#include "AutomatedParkingStructure.h"
#include "Terminal.h"
#include "Models/Vehicle.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include "TestHelpers/TestObjectGetter.h"
#include "TestHelpers/TestHelper.h"
#include <string>
#include <iostream>

using namespace std;

TestObjectGetter* testObjectGetter = new TestObjectGetter();
TestHelper* testHelper = new TestHelper(testObjectGetter);

bool TestAddAndRetrieveValidVehicleForNonMember()
{
    cout << "Testing adding and retrieving valid vehicle for non member" << "\n";
    cout << "----------------------------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 3);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    Ticket ticket = testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicleWasStored = testHelper->AssertSpaces(totalSpaces-1, availableSpaces);
    
    testHelper->RetrieveTestVehicle(terminal, aps, ticket, availableSpaces);
    bool vehicleWasRetrieved = testHelper->AssertSpaces(totalSpaces, availableSpaces);
    
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

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/memberCustomer.txt");
    
    Ticket ticket = testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicleWasStored = testHelper->AssertSpaces(totalSpaces-1, availableSpaces);
    
    testHelper->RetrieveTestVehicle(terminal, aps, ticket, availableSpaces);
    bool vehicleWasRetrieved = testHelper->AssertSpaces(totalSpaces, availableSpaces);

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

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/invalidVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    return testHelper->AssertSpaces(totalSpaces, availableSpaces);
}

bool TestNoSpaceToStoreVehicle()
{
    cout << "Testing no space to store vehicle" << "\n";
    cout << "---------------------------------" << "\n";
    
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(0, 0);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    return testHelper->AssertSpaces(totalSpaces, availableSpaces);
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

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(1, 2);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");

    Ticket ticket1 = testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicle1WasStored = testHelper->AssertSpaces(totalSpaces-1, availableSpaces);

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle2.txt", "inputs/nonMemberCustomer.txt");
    Ticket ticket2 = testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    bool vehicle2WasStored = testHelper->AssertSpaces(totalSpaces-2, availableSpaces);

    testHelper->RetrieveTestVehicle(terminal, aps, ticket2, availableSpaces);
    bool vehicle2WasRetrieved = testHelper->AssertSpaces(totalSpaces-1, availableSpaces);

    testHelper->RetrieveTestVehicle(terminal, aps, ticket1, availableSpaces);
    bool vehicle1WasRetrieved = testHelper->AssertSpaces(totalSpaces, availableSpaces);

    return (vehicle1WasStored && vehicle2WasStored) && (vehicle2WasRetrieved && vehicle1WasRetrieved);
}

bool TestRetrieveFromSecondFloor()
{
    cout << "Testing retrieving from second floor" << "\n";
    cout << "------------------------------------" << "\n";

    AutomatedParkingStructure* aps = new AutomatedParkingStructure(2, 2);
    Terminal* terminal = new Terminal(aps);

    int totalSpaces = aps->GetAvailableSpaces();
    int availableSpaces = totalSpaces;

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");

    for(int i = 0; i < totalSpaces-2; i++)
    {
        testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    }
    bool vehiclesWereStored = testHelper->AssertSpaces(2, availableSpaces);

    testHelper->LoadVehicleAndCustomer(terminal, "inputs/validVehicle2.txt", "inputs/nonMemberCustomer.txt");
    Ticket ticket = testHelper->StoreTestVehicle(terminal, aps, availableSpaces);
    bool desiredVehicleWasStored = testHelper->AssertSpaces(1, availableSpaces);

    testHelper->RetrieveTestVehicle(terminal, aps, ticket, availableSpaces);
    bool desiredVehicleWasRetrieved = testHelper->AssertSpaces(2, availableSpaces);

    return (vehiclesWereStored && desiredVehicleWasStored) && desiredVehicleWasRetrieved;
}

int main()
{
    bool results = TestAddAndRetrieveValidVehicleForNonMember();
    testHelper->PrintResults(results);
    
    results = TestAddAndRetrieveValidVehicleForMember();
    testHelper->PrintResults(results);
    
    results = TestRejectInvalidVehicle();
    testHelper->PrintResults(results);
    
    results = TestNoSpaceToStoreVehicle();
    testHelper->PrintResults(results);
    
    results = TestUpgradeNonMemberToMember();
    testHelper->PrintResults(results);
    
    results = TestNotUpgradeMember();
    testHelper->PrintResults(results);

    results = TestAddAndRetrieveTwoValidVehicleForNonMember();
    testHelper->PrintResults(results);
    
    results = TestRetrieveFromSecondFloor();
    testHelper->PrintResults(results);

    return 0;
}