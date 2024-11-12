#include "car.h"
#include "patient.h"

Car::Car(CarType type, int speed) : type(type), status(READY), speed(speed), currentPatient(nullptr) {}

void Car::assignPatient(Patient *patient)
{
    status = ASSIGNED;
    currentPatient = patient;
}

void Car::dropPatient()
{
    status = READY;
    currentPatient = nullptr;
}

Car::CarStatus Car::getStatus() const
{
    return status;
}

Car::CarType Car::getType() const
{
    return type;
}

int Car::getSpeed() const
{
    return speed;
}

Patient *Car::getCurrentPatient() const
{
    return currentPatient;
}
