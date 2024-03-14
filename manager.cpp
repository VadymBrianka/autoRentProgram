#include "manager.h"

Manager::Manager()
{

}

Manager::~Manager()
{

}

string Manager::getSurname()
{
    return Person::getSurname();
}

string Manager::getFirstName()
{
    return Person::getFirstName();
}

string Manager::getMiddleName()
{
    return Person::getMiddleName();
}

string Manager::getEmail()
{
    return Person::getEmail();
}

string Manager::getPhoneNumber()
{
    return Person::getPhoneNumber();
}

string Manager::getLogin()
{
    return login;
}

string Manager::getPassword()
{
    return password;
}

string Manager::getSecretQuestion()
{
    return secretQuestion;
}

string Manager::getAnswerToSecretQuestion()
{
    return answerToSecretQuestion;
}

string Manager::getRole()
{
    return role;
}

string Manager::getStatus()
{
    return status;
}

void Manager::setLogin(string login)
{
    this->login = login;
}

void Manager::setPassword(string password)
{
    this->password = password;
}

void Manager::setSecretQuestion(string secretQuestion)
{
    this->secretQuestion = secretQuestion;
}

void Manager::setAnswerToSecretQuestion(string answerToSecretQuestion)
{
    this->answerToSecretQuestion = answerToSecretQuestion;
}

void Manager::setRole(string role)
{
    this->role = role;
}

void Manager::setStatus(string status)
{
    this->status = status;
}

void Manager::setSurname(string surname)
{
    Person::setSurname(surname);
}

void Manager::setFirstName(string firstName)
{
    Person::setFirstName(firstName);
}

void Manager::setMiddleName(string middleName)
{
    Person::setMiddleName(middleName);
}

void Manager::setEmail(string email)
{
    Person::setEmail(email);
}

void Manager::setPhoneNumber(string phoneNumber)
{
    Person::setPhoneNumber(phoneNumber);
}
