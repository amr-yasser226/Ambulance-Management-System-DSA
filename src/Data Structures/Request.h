#ifndef REQUEST_H
#define REQUEST_H

class Patient;
class Car;

struct Request
{
    Request() :
        patient(Patient()),
        type(Car::CarType::NC),
        status(Car::CarStatus::READY),
        nearestHospitalDistance(0),
        QT(0.0),
        AT(0.0),
        PT(0.0),
        WT(0.0),
        FT(0.0),
        carBusyTime(0.0)
    {}

    Request(
        Patient patient,
        Car::CarType type,
        Car::CarStatus status,
        int nearestHospitalDistance,
        double QT,
        double AT,
        double PT,
        double WT,
        double FT,
        double carBusyTime
    ) :
        patient(patient),
        type(type),
        status(status),
        nearestHospitalDistance(nearestHospitalDistance),
        QT(QT),
        AT(AT),
        PT(PT),
        WT(WT),
        FT(FT),
        carBusyTime(carBusyTime)
    {}

    Patient patient;
    Car::CarType type;
    Car::CarStatus status;
    int nearestHospitalDistance;
    double QT;
    double AT;
    double PT;
    double WT;
    double FT;
    double carBusyTime;
};

#endif // REQUEST_H