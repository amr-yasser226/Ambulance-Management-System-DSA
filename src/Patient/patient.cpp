#include "patient.h"

Patient::Patient() : 
    type(NP),
    pid(0),
    nearestHospitalID(0),
    nearestHospitalDistance(0),
    QT(0.0),
    AT(0.0),
    PT(0.0),
    WT(0.0),
    FT(0.0),
    carBusytime(0.0)
{
}

Patient::Patient(int patientID, int hospitalID, int hospitalDistance, PatientType patientType) :
    pid(patientID),
    nearestHospitalID(hospitalID),
    nearestHospitalDistance(hospitalDistance),
    type(patientType),
    QT(0.0),
    AT(0.0),
    PT(0.0),
    WT(0.0),
    FT(0.0),
    carBusytime(0.0)
{
}

PatientType Patient::getType() const { return type; }

int Patient::getPID() const { return pid; }
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
    std::cout << "Patient Details:" << std::endl;
    std::cout << "Patient ID: " << pid << std::endl;
    std::cout << "Patient Type: ";
    switch (type)
    {
        case NP: std::cout << "Normal Patient"; break;
        case SP: std::cout << "Special Patient"; break;
        case EP: std::cout << "Emergency Patient"; break;
    }
    std::cout << std::endl;
    std::cout << "Nearest Hospital ID: " << nearestHospitalID << std::endl;
    std::cout << "Nearest Hospital Distance: " << nearestHospitalDistance << std::endl;
    std::cout << "Request Time (QT): " << QT << std::endl;
    std::cout << "Arrival Time (AT): " << AT << std::endl;
    std::cout << "Pickup Time (PT): " << PT << std::endl;
    std::cout << "Waiting Time (WT): " << WT << std::endl;
    std::cout << "Finish Time (FT): " << FT << std::endl;
    std::cout << "Car Busy Time: " << carBusytime << std::endl;
}