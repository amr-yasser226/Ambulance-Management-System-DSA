#ifndef CAR_H
#define CAR_H

#include <iostream>

class Patient;

class Car
{
public:
    enum CarType
    {
        SC, // Special Car
        NC  // Normal Car
    };

    enum CarStatus
    {
        READY,
        ASSIGNED,
        LOADED
    };

private:
    CarType type;
    CarStatus status;
    int speed;
    Patient *currentPatient;

public:
    Car(CarType type, int speed);

    void assignPatient(Patient *patient);
    void dropPatient();
    CarStatus getStatus() const;
    CarType getType() const;
    int getSpeed() const;
    Patient *getCurrentPatient() const;
};

#endif // CAR_H
