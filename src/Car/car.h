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
    int uniqueID;

public:
    Car();
    Car(CarType carType, int carID);

    CarType getCarType() const;
    CarStatus getCarStatus() const;
    Patient* getCurrentPatient() const;

    int getUniqueID();

    void setUniqueID(int newCarID);
    void setCarStatus(CarStatus newStatus);
    void setCurrentPatient(Patient* patient);
    void clearRidingPatient();

    void printDetails() const;
};
#endif // CAR_H