#include <string>
#include "Vehicle.h"

using namespace std;

class Vehicle
{
    private:
        string licensePlate;
        string make;
        string model;
        int year;
        double weight;
        int wheels;
    public:
        Vehicle(string, string, string, int, double, int);
        string GetlicensePlate();
        double GetWeight();
        int GetWheels();
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