#include "Terminal.h"
#include "Models/Vehicle.h"
#include "Models/Customer.h"
#include "Models/Ticket.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Vehicle* createVehicle(string fileName)
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

Customer* createCustomer(string fileName)
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

void loadVehicleAndCustomer(Terminal* terminal, string vehicleFile, string customerFile)
{
    Vehicle* vehicle = createVehicle(vehicleFile);
    Customer* customer = createCustomer(customerFile);
    terminal->SetCurrentVehicle(vehicle);
    terminal->SetCurrentCustomer(customer);
}

void testAddAndRetrieveValidVehicle()
{
    cout << "Testing adding and retrieving valid vehicle" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/validVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    Ticket ticket = terminal->StoreCurrentVehicle();
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == 99)
    {
        cout << "Vehicle added!" << "\n";
    }

    terminal->RetrieveVehicle(ticket);
    availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == 100)
    {
        cout << "Vehicle retrieved!" << "\n";
    }
}

void testRejectInvalidVehicle()
{
    cout << "Testing adding and retrieving invalid vehicle" << "\n\n";

    int totalSpaces = 100;
    AutomatedParkingStructure* aps = new AutomatedParkingStructure(totalSpaces);
    Terminal* terminal = new Terminal(aps);

    loadVehicleAndCustomer(terminal, "inputs/invalidVehicle.txt", "inputs/nonMemberCustomer.txt");
    
    terminal->StoreCurrentVehicle();
    int availableSpaces = aps->GetAvailableSpaces();
    if(availableSpaces == 100)
    {
        cout << "Vehicle correctly rejected!" << "\n";
    }
}

int main()
{
    testAddAndRetrieveValidVehicle();
    cout << "\n";
    testRejectInvalidVehicle();

    return 0;
}