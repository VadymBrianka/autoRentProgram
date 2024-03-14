#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;
class Customer : public Person {
private:
    int age;
    int yearsOfExperience;
    string address;
    string ITIN;
    string status;
public:
    virtual string getSurname() override;
    virtual string getFirstName() override;
    virtual string getMiddleName() override;
    virtual string getEmail() override;
    virtual string getPhoneNumber() override;
    virtual int getAge();
    virtual int getYearsOfExperience();
    virtual string getAddress();
    virtual string getITIN();
    virtual string getStatus();

    virtual void setSurname(string surname) override;
    virtual void setFirstName(string firstName) override;
    virtual void setMiddleName(string middleName) override;
    virtual void setEmail(string email) override;
    virtual void setPhoneNumber(string phoneNumber) override;
    virtual void setAge(int age);
    virtual void setYearsOfExperience(int yearsOfExperience);
    virtual void setAddress(string address);
    virtual void setITIN(string ITIN);
    virtual void setStatus(string status);
    Customer();
    ~Customer();
};
#endif // CUSTOMER_H
