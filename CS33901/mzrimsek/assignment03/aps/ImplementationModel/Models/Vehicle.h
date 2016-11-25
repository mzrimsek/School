#ifndef Vehicle_H
#define Vehicle_H

#include <string>

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
};

#endif