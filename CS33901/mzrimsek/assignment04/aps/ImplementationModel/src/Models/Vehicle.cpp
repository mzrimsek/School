#include <string>
#include "Vehicle.h"

Vehicle::Vehicle()
{
    licensePlate = "";
    make = "";
    model = "";
    year = 0;
    weight = 0;
    wheels = 0;
}

Vehicle::Vehicle(string tLicensePlate, string tMake, string tModel, int tYear, double tWeight, int tWheels)
{
    licensePlate = tLicensePlate;
    make = tMake;
    model = tModel;
    year = tYear;
    weight = tWeight;
    wheels = tWheels;
}

string Vehicle::GetLicensePlate()
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