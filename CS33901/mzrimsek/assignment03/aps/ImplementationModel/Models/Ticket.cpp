#include <string>
#include "Ticket.h"

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
}

Ticket::Ticket(string tCustomerName, string tVehicleLicensePlate)
{
    customerName = tCustomerName;
    vehicleLicensePlate = tVehicleLicensePlate;
}

string Ticket::GetCustomerName()
{
    return customerName;
}

string Ticket::GetVehicleLicensePlate()
{
    return vehicleLicensePlate;
}