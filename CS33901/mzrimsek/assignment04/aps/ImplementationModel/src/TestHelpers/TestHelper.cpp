#include "TestHelper.h"
#include <string>
#include <iostream>
#include "../AutomatedParkingStructure.h"
#include "../Terminal.h"
#include "../Models/Customer.h"
#include "../Models/Ticket.h"
#include "../Models/Vehicle.h"

TestHelper::TestHelper(TestObjectGetter* tTestObjectGetter)
{
    testObjectGetter = tTestObjectGetter;
}

void TestHelper::LoadVehicleAndCustomer(Terminal* terminal, string vehicleFile, string customerFile)
{
    Vehicle* vehicle = testObjectGetter->GetVehicle(vehicleFile);
    Customer* customer = testObjectGetter->GetCustomer(customerFile);
    terminal->SetCurrentVehicle(vehicle);
    terminal->SetCurrentCustomer(customer);
}

Ticket TestHelper::StoreTestVehicle(Terminal* terminal, AutomatedParkingStructure* aps, int& availableSpaces)
{
    Ticket ticket = terminal->StoreCurrentVehicle(10);
    availableSpaces = aps->GetAvailableSpaces();
    return ticket;
}

void TestHelper::RetrieveTestVehicle(Terminal* terminal, AutomatedParkingStructure* aps, Ticket ticket, int& availableSpaces)
{
    terminal->RetrieveVehicle(ticket);
    availableSpaces = aps->GetAvailableSpaces();
}

bool TestHelper::AssertSpaces(int expectedSpaces, int actualSpaces)
{
    return expectedSpaces == actualSpaces;
}

void TestHelper::PrintResults(bool testResults)
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