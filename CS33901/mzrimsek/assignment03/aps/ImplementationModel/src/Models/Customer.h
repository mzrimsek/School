#ifndef Customer_H
#define Customer_H

#include <string>

using namespace std;

class Customer
{
    private:
        string firstName;
        string lastName;
        bool isMember;
    public:
        Customer(string, string, bool);
        string GetName();
        bool GetIsMember();
        void SetIsMember(bool);
};

#endif