#include "admin.h"

Admin::Admin()
{

}

Admin::~Admin()
{

}

string Admin::getSurname()
{
    return Person::getSurname();
}

string Admin::getFirstName()
{
    return Person::getFirstName();
}

string Admin::getMiddleName()
{
    return Person::getMiddleName();
}

string Admin::getEmail()
{
    return Person::getEmail();
}

string Admin::getPhoneNumber()
{
    return Person::getPhoneNumber();
}

string Admin::getLogin()
{
    return login;
}

string Admin::getPassword()
{
    return password;
}

string Admin::getSecretQuestion()
{
    return secretQuestion;
}

string Admin::getAnswerToSecretQuestion()
{
    return answerToSecretQuestion;
}

string Admin::getRole()
{
    return role;
}

string Admin::getStatus()
{
    return status;
}

void Admin::setLogin(string login)
{
    this->login = login;
}

void Admin::setPassword(string password)
{
    this->password = password;
}

void Admin::setSecretQuestion(string secretQuestion)
{
    this->secretQuestion = secretQuestion;
}

void Admin::setAnswerToSecretQuestion(string answerToSecretQuestion)
{
    this->answerToSecretQuestion = answerToSecretQuestion;
}

void Admin::setRole(string role)
{
    this->role = role;
}

void Admin::setStatus(string status)
{
    this->status = status;
}

void Admin::setSurname(string surname)
{
    Person::setSurname(surname);
}

void Admin::setFirstName(string firstName)
{
    Person::setFirstName(firstName);
}

void Admin::setMiddleName(string middleName)
{
    Person::setMiddleName(middleName);
}

void Admin::setEmail(string email)
{
    Person::setEmail(email);
}

void Admin::setPhoneNumber(string phoneNumber)
{
    Person::setPhoneNumber(phoneNumber);
}
