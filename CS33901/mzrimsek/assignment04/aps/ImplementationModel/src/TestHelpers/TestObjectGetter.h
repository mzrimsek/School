#ifndef TestObjectGetter_H
#define TestObjectGetter_H

#include <string>
#include "../Models/Customer.h"
#include "../Models/Vehicle.h"

using namespace std;

class TestObjectGetter
{
    public:
        TestObjectGetter();
        Vehicle* GetVehicle(string);
        Customer* GetCustomer(string);
};

#endif