#ifndef DEAL_H
#define DEAL_H
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Deal
{
private:
    string itin;
    string vin;
    string rentStartDate;
    string rentEndDate;
    string status;
    string check;
    string payment;
public:
    virtual string getItin();
    virtual string getVin();
    virtual string getRentStartDate();
    virtual string getRentEndDate();
    virtual string getStatus();
    virtual string getCheck();
    virtual string getPayment();

    virtual void setItin(string itin);
    virtual void setVin(string vin);
    virtual void setRentStartDate(string rentStartDate);
    virtual void setRentEndDate(string rentEndDate);
    virtual void setStatus(string status);
    virtual void setCheck(string check);
    virtual void setPayment(string payment);
    Deal();
    ~Deal();
};

#endif // DEAL_H
