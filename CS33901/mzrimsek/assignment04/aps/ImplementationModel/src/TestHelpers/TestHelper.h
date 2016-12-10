#ifndef TestHelper_H
#define TestHelper_H

#include <string>
#include "../AutomatedParkingStructure.h"
#include "../Terminal.h"
#include "../Models/Customer.h"
#include "../Models/Ticket.h"
#include "../Models/Vehicle.h"
#include "TestObjectGetter.h"

using namespace std;

class TestHelper
{
    private:
        TestObjectGetter* testObjectGetter;
    public:
        TestHelper(TestObjectGetter*);
        void LoadVehicleAndCustomer(Terminal*, string, string);
        Ticket StoreTestVehicle(Terminal*, AutomatedParkingStructure*, int&);
        void RetrieveTestVehicle(Terminal*, AutomatedParkingStructure*, Ticket, int&);
        bool AssertSpaces(int, int);
        void PrintResults(bool);
};

#endif