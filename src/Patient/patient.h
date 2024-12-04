#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>

class Patient
{
public:
    enum PatientType
    {
        NP, // 0
        SP, // 1
        EP  // 2
    };

private:
    int pid;
    int nearestHospitalID;
    int nearestHospitalDistance;
    PatientType type;
    double QT, AT, PT, WT, FT, carBusytime;

public:
    Patient();
    Patient(int patientID, int hospitalID, int hospitalDistance, PatientType patientType);
    
    PatientType getType() const;
    int getPID() const;
    int getNearestHospitalID() const;
    int getNearestHospitalDistance() const;
    
    double getQT() const;
    double getAT() const;
    double getPT() const;
    double getWT() const;
    double getFT() const;
    double getCarBusyTime() const;
    
    void printDetails();
};
#endif // PATIENT_H