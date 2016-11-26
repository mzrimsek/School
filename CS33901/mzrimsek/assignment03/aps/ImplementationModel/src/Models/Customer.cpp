#include <string>
#include "Customer.h"

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