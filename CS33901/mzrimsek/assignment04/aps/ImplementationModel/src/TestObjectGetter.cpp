#include "TestObjectGetter.h"
#include <string>
#include <fstream>

TestObjectGetter::TestObjectGetter(){}

Vehicle* TestObjectGetter::GetVehicle(string fileName)
{
    ifstream inputFile(fileName.c_str());

    string* lines = new string[6];
    if(inputFile.is_open())
    {
        int index = 0;
        while(getline(inputFile, lines[index]))
        {
            index++;
        }
    }
    inputFile.close();

    string licensePlate = lines[0];
    string make = lines[1];
    string model = lines[2];
    int year = stoi(lines[3]);
    double weight = stod(lines[4]);
    int wheels = stoi(lines[5]);

    return new Vehicle(licensePlate, make, model, year, weight, wheels);
}

Customer* TestObjectGetter::GetCustomer(string fileName)
{
    ifstream inputFile(fileName.c_str());

    string* lines = new string[3];
    if(inputFile.is_open())
    {
        int index = 0;
        while(getline(inputFile, lines[index]))
        {
            index++;
        }
    }
    inputFile.close();

    string firstName = lines[0];
    string lastName = lines[1];
    bool isMember = lines[2].compare("True")==0;

    return new Customer(firstName, lastName, isMember);
}