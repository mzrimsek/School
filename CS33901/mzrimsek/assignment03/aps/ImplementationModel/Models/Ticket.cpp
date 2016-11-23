#include <string>
#include "Ticket.h"

using namespace std;

class Ticket
{
    private:
        string customerName;
        int vehiclePosition;
    public:
        Ticket(string, int);
        string GetCustomerName();
        int GetVehiclePosition();
}

Ticket::Ticket(string tCustomerName, int tVehiclePosition)
{
    customerName = tCustomerName;
    vehiclePosition = tVehiclePosition;
}

string Ticket::GetCustomerName()
{
    return customerName;
}

int Ticket::GetVehiclePosition()
{
    return vehiclePosition;
}