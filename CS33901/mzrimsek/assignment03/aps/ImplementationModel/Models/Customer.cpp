#include <string>
#include "Customer.h"

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
}

Customer::Customer(string tFirstName, string tLastName, bool tIsMember)
{
    firstName = tFirstName;
    lastName = tLastName;
    isMember = tIsMember;
}

string Customer::GetName()
{
    return firstName + " " + lastName;
}

bool Customer::GetIsMember()
{
    return isMember;
}

void Customer::SetIsMember(bool tIsMember)
{
    isMember = tIsMember;
}