#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class Car
{
private:
    string brand;
    string model;
    int year;
    string vin;
    float engineCapacity;
    int numberOfSeats;
    int trunkVolume;
    int priceOfRenting;
    int price;
    string userId;
    string status;

public:
    virtual string getBrand();
    virtual string getModel();
    virtual int getYear();
    virtual string getVin();
    virtual float getEngineCapacity();
    virtual int getNumberOfSeats();
    virtual int getTrunkVolume();
    virtual int getPriceOfRenting();
    virtual int getPrice();
    virtual string getStatus();

    virtual void setBrand(string brand);
    virtual void setModel(string model);
    virtual void setYear(int year);
    virtual void setVin(string vin);
    virtual void setEngineCapacity(float engineCapacity);
    virtual void setNumberOfSeats(int numberOfSeats);
    virtual void setTrunkVolume(int trunkVolume);
    virtual void setPriceOfRenting(int priceOfRenting);
    virtual void setPrice(int price);
    virtual void setStatus(string status);

    Car();
    ~Car();
};


#endif // CAR_H
