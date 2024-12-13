#include "patient.h"

Patient::Patient() :
    pid(0),
    severity(0),
    nearestHospitalID(0),
    nearestHospitalDistance(0),
    type(NP),
    QT(0.0),
    AT(0.0),
    PT(0.0),
    WT(0.0),
    FT(0.0),
    carBusytime(0.0)
{}

Patient::Patient(int requestTime, int patientID, int hospitalID, int hospitalDistance, PatientType patientType, int severity) :
    pid(patientID),
    severity(severity),
    nearestHospitalID(hospitalID),
    nearestHospitalDistance(hospitalDistance),
    type(patientType),
    QT(requestTime),
    AT(0.0),
    PT(0.0),
    WT(0.0),
    FT(0.0),
    carBusytime(0.0)
{}

Patient::PatientType Patient::getType() const { return type; }

int Patient::getPID() const { return pid; }
int Patient::getSeverity() const { return severity; }
int Patient::getNearestHospitalID() const { return nearestHospitalID; }
int Patient::getNearestHospitalDistance() const { return nearestHospitalDistance; }

double Patient::getQT() const { return QT; }
double Patient::getAT() const { return AT; }
double Patient::getPT() const { return PT; }
double Patient::getWT() const { return WT; }
double Patient::getFT() const { return FT; }
double Patient::getCarBusyTime() const { return carBusytime; }

void Patient::printDetails()
{
    std::cout << std::endl;
    std::cout << "PATIENT | ID: " << pid << " | Type: ";
    switch (type)
    {
        case NP: std::cout << "Normal Patient"; break;
        case SP: std::cout << "Special Patient"; break;
        case EP: std::cout << "Emergency Patient"; break;
    }
    std::cout << std::endl;
    std::cout << "PATIENT | nearest HID: " << nearestHospitalID << " | nearest HDistance: " << nearestHospitalDistance << std::endl;
    std::cout << "| QT: " << QT << " | AT: " << AT << " | PT: " << PT << " | WT: " << WT << " | FT: " << FT << " | Car Busy Time: " << carBusytime << std::endl;
    std::cout << std::endl;
}