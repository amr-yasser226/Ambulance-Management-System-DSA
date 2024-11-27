#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

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
    std::string firstName;
    std::string middleName;
    std::string lastName;
    int pid;
    int requestTime; // most likely will be removed
    int severity;
    PatientType type;
    int nearestHospitalID;

public:
    Patient();

    void setPID(int pid);
    int getPID();

    // Removed methods related to user input
    void setFirstName(const std::string &name);
    void setMiddleName(const std::string &name);
    void setLastName(const std::string &name);
    void setNearestHospitalID(int ID);

    const std::string &getFirstName() const;
    const std::string &getMiddleName() const;
    const std::string &getLastName() const;

    int getRequestTime() const;
    int getSeverity() const;

    PatientType getType() const;
    void setPatientType(PatientType type);

    int getNearestHospitalID() const;
    void printDetails() const;

    void setSeverity(int severity);
};

#endif // PATIENT_H
