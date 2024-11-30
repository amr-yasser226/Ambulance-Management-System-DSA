#ifndef CAR_H
#define CAR_H

#include <iostream>
#include "../Patient/patient.h"

class Car
{
public:
    enum CarType
    {
        SC, // 0
        NC  // 1
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
    Patient *currentPatient;

public:
    Car();
    Car(CarType carType);

    CarType getCarType() const;
    CarStatus getCarStatus() const;
    Patient* getCurrentPatient() const;

    void setCarStatus(CarStatus newStatus);
    void setCurrentPatient(Patient* patient);

    void printDetails() const;
};
#endif // CAR_H