#ifndef REQUEST_H
#define REQUEST_H

struct Request
{
    Request() : 
        patient(Patient()),
        type(Car::CarType::NC),
        status(Car::CarStatus::READY),
        nearestHospitalDistance(0),
        QT(0),
        PT(0),
        WT(0),
        FT(0),
        carBusyTime(0)
    {}

    Patient patient;
    Car::CarType type;
    Car::CarStatus status;
    int nearestHospitalDistance;
    int QT;
    int PT;
    int WT;
    int FT;
    int carBusyTime;

    Request(
        Patient patient,
        Car::CarType type,
        Car::CarStatus status,
        int nearestHospitalDistance,
        int QT,
        int PT,
        int WT,
        int FT,
        int carBusyTime
    ) : 
        patient(patient),
        type(type),
        status(status),
        nearestHospitalDistance(nearestHospitalDistance),
        QT(QT),
        PT(PT),
        WT(WT),
        FT(FT),
        carBusyTime(carBusyTime)
    {}
};

#endif // REQUEST_H