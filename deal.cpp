#include "deal.h"

string Deal::getItin()
{
    return itin;
}

string Deal::getVin()
{
    return vin;
}

string Deal::getRentStartDate()
{
    return rentStartDate;
}

string Deal::getRentEndDate()
{
    return rentEndDate;
}

string Deal::getStatus()
{
    return status;
}

string Deal::getCheck()
{
    return check;
}

string Deal::getPayment()
{
    return payment;
}

void Deal::setItin(string itin)
{
    this->itin = itin;
}

void Deal::setVin(string vin)
{
    this->vin = vin;
}

void Deal::setRentStartDate(string rentStartDate)
{
    this->rentStartDate = rentStartDate;
}

void Deal::setRentEndDate(string rentEndDate)
{
    this->rentEndDate = rentEndDate;
}

void Deal::setStatus(string status)
{
    this->status = status;
}

void Deal::setCheck(string check)
{
    this->check = check;
}

void Deal::setPayment(string payment)
{
    this->payment = payment;
}

Deal::Deal()
{

}

Deal::~Deal()
{

}
