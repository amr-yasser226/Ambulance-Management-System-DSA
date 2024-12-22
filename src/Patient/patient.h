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
    int pid = 0;
    int severity = 0;
    int cancelled = 0;
    int nearestHospitalID = 0;
    int nearestHospitalDistance = 0;
    PatientType type;
    double QT = 0, AT = 0, PT = 0, WT = 0, FT = 0, carBusytime = 0;

public:
    Patient();
    Patient(int requestTime, int patientID, int hospitalID, int hospitalDistance, PatientType patientType, int severity);

    PatientType getType() const;
    int getPID() const;
    int getSeverity() const;
    int getNearestHospitalID() const;
    int getNearestHospitalDistance() const;
    
    double getQT() const;
    double getAT() const;
    double getPT() const;
    double getWT() const;
    double getFT() const;
    double getCarBusyTime() const;

    void setCancelled();
    void setAT(double value);
    void setPT(double value);
    void setWT(double value);
    void setFT(double value);
    void setCarBusyTime(double value);
    
    void printDetails();
};

#endif // PATIENT_H