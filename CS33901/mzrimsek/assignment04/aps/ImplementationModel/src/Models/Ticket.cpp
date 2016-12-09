#include <string>
#include "Ticket.h"

Ticket::Ticket(string tCustomerName, string tVehicleLicensePlate, int tTimeToStore)
{
    customerName = tCustomerName;
    vehicleLicensePlate = tVehicleLicensePlate;
    timeToStore = tTimeToStore;
}

string Ticket::GetCustomerName()
{
    return customerName;
}

string Ticket::GetVehicleLicensePlate()
{
    return vehicleLicensePlate;
}

int Ticket::GetTimeToStore()
{
    return timeToStore;
}