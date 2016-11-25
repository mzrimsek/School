#include <string>
#include "Vehicle.h"

Vehicle::Vehicle(string tLicensePlate, string tMake, string tModel, int tYear, double tWeight, int tWheels)
{
    licensePlate = tLicensePlate;
    make = tMake;
    model = tModel;
    year = tYear;
    weight = tWeight;
    wheels = tWheels;
}

string Vehicle::GetlicensePlate()
{
    return licensePlate;
}

double Vehicle::GetWeight()
{
    return weight;
}

int Vehicle::GetWheels()
{
    return wheels;
}