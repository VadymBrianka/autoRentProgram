#include "person.h"

string Person::getSurname()
{
    return surname;
}

string Person::getFirstName()
{
    return firstName;
}

string Person::getMiddleName()
{
    return middleName;
}

string Person::getEmail()
{
    return email;
}

string Person::getPhoneNumber()
{
    return phoneNumber;
}

void Person::setSurname(string surname)
{
    this->surname = surname;
}

void Person::setFirstName(string firstName)
{
    this->firstName = firstName;
}

void Person::setMiddleName(string middleName)
{
    this->middleName = middleName;
}

void Person::setEmail(string email)
{
    this->email = email;
}

void Person::setPhoneNumber(string phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

Person::Person(){}

Person::~Person(){}
