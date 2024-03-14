#include "customer.h"

string Customer::getSurname()
{
    return Person::getSurname();
}

string Customer::getFirstName()
{
    return Person::getFirstName();
}

string Customer::getMiddleName()
{
    return Person::getMiddleName();
}

string Customer::getEmail()
{
    return Person::getEmail();
}

string Customer::getPhoneNumber()
{
    return Person::getPhoneNumber();
}

int Customer::getAge()
{
     return age;
}

int Customer::getYearsOfExperience()
{
     return yearsOfExperience;
}

string Customer::getAddress()
{
     return address;
}

string Customer::getITIN()
{
     return ITIN;
}

string Customer::getStatus()
{
     return status;
}

void Customer::setSurname(string surname)
{
    Person::setSurname(surname);
}

void Customer::setFirstName(string firstName)
{
    Person::setFirstName(firstName);
}

void Customer::setMiddleName(string middleName)
{
    Person::setMiddleName(middleName);
}

void Customer::setEmail(string email)
{
    Person::setEmail(email);
}

void Customer::setPhoneNumber(string phoneNumber)
{
    Person::setPhoneNumber(phoneNumber);
}

void Customer::setAge(int age)
{
    this->age = age;
}

void Customer::setYearsOfExperience(int yearsOfExperience)
{
    this->yearsOfExperience = yearsOfExperience;
}

void Customer::setAddress(string address)
{
    this->address = address;
}

void Customer::setITIN(string ITIN)
{
    this->ITIN = ITIN;
}

void Customer::setStatus(string status)
{
    this->status = status;
}

Customer::Customer()
{

}

Customer::~Customer()
{

}
