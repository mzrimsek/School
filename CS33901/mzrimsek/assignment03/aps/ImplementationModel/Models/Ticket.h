#ifndef Ticket_H
#define Ticket_H

#include <string>

using namespace std;

class Ticket
{
    private:
        string customerName;
        string vehicleLicensePlate;
    public:
        Ticket(string, string);
        string GetCustomerName();
        string GetVehicleLicensePlate();
};

#endif