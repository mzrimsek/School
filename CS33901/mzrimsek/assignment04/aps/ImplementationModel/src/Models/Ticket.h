#ifndef Ticket_H
#define Ticket_H

#include <string>

using namespace std;

class Ticket
{
    private:
        string customerName;
        string vehicleLicensePlate;
        int timeToStore;
    public:
        Ticket(string, string, int);
        string GetCustomerName();
        string GetVehicleLicensePlate();
        int GetTimeToStore();
};

#endif