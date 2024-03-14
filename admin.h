#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "Person.h"
using namespace std;
class Admin : public Person {
private:
    string login;
    string password;
    string secretQuestion;
    string answerToSecretQuestion;
    string role;
    string status;

public:
    virtual string getSurname() override;
    virtual string getFirstName() override;
    virtual string getMiddleName() override;
    virtual string getEmail() override;
    virtual string getPhoneNumber() override;
    virtual string getLogin();
    virtual string getPassword();
    virtual string getSecretQuestion();
    virtual string getAnswerToSecretQuestion();
    virtual string getRole();
    virtual string getStatus();

    virtual void setSurname(string surname) override;
    virtual void setFirstName(string firstName) override;
    virtual void setEmail(string email) override;
    virtual void setMiddleName(string firstName) override;
    virtual void setPhoneNumber(string phoneNumber) override;
    virtual void setLogin(string login);
    virtual void setPassword(string password);
    virtual void setSecretQuestion(string secretQuestion);
    virtual void setAnswerToSecretQuestion(string answerToSecretQuestion);
    virtual void setRole(string role);
    virtual void setStatus(string status);
    Admin();
    ~Admin();
};

#endif // ADMIN_H
