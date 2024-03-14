#include "car.h"

string Car::getBrand()
{
    return brand;
}

string Car::getModel()
{
    return model;
}

int Car::getYear()
{
    return year;
}

string Car::getVin()
{
    return vin;
}

float Car::getEngineCapacity()
{
    return engineCapacity;
}

int Car::getNumberOfSeats()
{
    return numberOfSeats;
}

int Car::getTrunkVolume()
{
    return trunkVolume;
}

int Car::getPriceOfRenting()
{
    return priceOfRenting;
}

int Car::getPrice()
{
    return price;
}

string Car::getStatus()
{
    return status;
}

void Car::setBrand(string brand)
{
    this->brand = brand;
}

void Car::setModel(string model)
{
    this->model = model;
}

void Car::setYear(int year)
{
    this->year = year;
}

void Car::setVin(string vin)
{
    this->vin = vin;
}

void Car::setEngineCapacity(float engineCapacity)
{
    this->engineCapacity = engineCapacity;
}

void Car::setNumberOfSeats(int numberOfSeats)
{
    this->numberOfSeats = numberOfSeats;
}

void Car::setTrunkVolume(int trunkVolume)
{
    this->trunkVolume = trunkVolume;
}

void Car::setPriceOfRenting(int priceOfRenting)
{
    this->priceOfRenting = priceOfRenting;
}

void Car::setPrice(int price)
{
    this->price = price;
}

void Car::setStatus(string status)
{
    this->status = status;
}

Car::Car()
{

}

Car::~Car()
{

}
