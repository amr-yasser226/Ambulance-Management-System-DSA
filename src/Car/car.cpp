#include "car.h"

Car::Car() : type(NC), status(READY), currentPatient(nullptr), uniqueID(0)
{
}

Car::Car(CarType carType, int carID) : type(carType), status(READY), currentPatient(nullptr), uniqueID(carID)
{
}

Car::CarType Car::getCarType() const
{
    return type;
}

Car::CarStatus Car::getCarStatus() const
{
    return status;
}

Patient* Car::getCurrentPatient() const
{
    return currentPatient;
}

int Car::getUniqueID()
{
    return uniqueID;
}

void Car::setUniqueID(int newCarID)
{
    uniqueID = newCarID;
}

void Car::setCarStatus(CarStatus newStatus)
{
    status = newStatus;
}


void Car::setCurrentPatient(Patient* patient)
{
    currentPatient = patient;
}

void Car::clearRidingPatient()
{
    delete currentPatient;
}

void Car::printDetails() const
{
    std::cout << "Car Details:" << std::endl;
    
    std::cout << "Car Type: ";
    switch (type)
    {
        case SC: std::cout << "Special Car"; break;
        case NC: std::cout << "Normal Car"; break;
    }
    std::cout << std::endl;
    
    std::cout << "Car Status: ";
    switch (status)
    {
        case READY: std::cout << "Ready"; break;
        case ASSIGNED: std::cout << "Assigned"; break;
        case LOADED: std::cout << "Loaded"; break;
    }
    std::cout << std::endl;

    if (currentPatient)
    {
        std::cout << "Current Patient Details:" << std::endl;
        currentPatient->printDetails();
    }
    else
    {
        std::cout << "No patient assigned" << std::endl;
    }
}