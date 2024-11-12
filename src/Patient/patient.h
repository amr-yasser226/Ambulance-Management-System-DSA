#ifndef PATIENT_H
#define PATIENT_H

#include <iostream> // Only include iostream; std::string will still work

class Patient
{
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    int requestTime;
    int severity; // Only relevant for EP patients
    enum PatientType
    {
        NP,
        SP,
        EP
    } type;
    int nearestHospitalID;

public:
    // Constructor
    Patient();

    // Method to perform all input and output actions in one call
    void collectAndDisplayPatientInfo();

private:
    // Methods to get input from the patient
    void getFirstName();
    void getMiddleName();
    void getLastName();

    // Method to print patient details
    void printDetails() const;

    // Helper functions for validation
    bool isEnglishLetter(char c);
    bool isValidName(const std::string &name);
    void getNameInput(std::string &name, const std::string &prompt);
};

#endif // PATIENT_H
