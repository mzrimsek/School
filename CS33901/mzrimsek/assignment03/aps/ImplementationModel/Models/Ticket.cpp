#include <string>
#include "Ticket.h"

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