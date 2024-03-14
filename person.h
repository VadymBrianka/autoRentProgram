#ifndef PERSON_H
#define PERSON_H
#include <iostream>

using namespace std;
class Person {
private:
    string surname;
    string firstName;
    string middleName;
    string email;
    string phoneNumber;

public:
    virtual string getSurname();
    virtual string getFirstName();
    virtual string getMiddleName();
    virtual string getEmail();
    virtual string getPhoneNumber();

    virtual void setSurname(string surname);
    virtual void setFirstName(string firstName);
    virtual void setMiddleName(string middleName);
    virtual void setEmail(string email);
    virtual void setPhoneNumber(string phoneNumber);
    Person();
    ~Person();
};
#endif // PERSON_H
