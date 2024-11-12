#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>

class Patient
{
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    int requestTime;
    int severity;
    enum PatientType
    {
        NP,
        SP,
        EP
    } type;
    int nearestHospitalID;

public:
    Patient();

    void collectAndDisplayPatientInfo();

private:
    void getFirstName();
    void getMiddleName();
    void getLastName();

    void printDetails() const;

    bool isEnglishLetter(char c);
    bool isValidName(const std::string &name);
    void getNameInput(std::string &name, const std::string &prompt);
};

#endif // PATIENT_H
