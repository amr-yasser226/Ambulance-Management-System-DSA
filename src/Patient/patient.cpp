#include "patient.h"

Patient::Patient() : requestTime(0), severity(0), type(NP), nearestHospitalID(0) {}

void Patient::setFirstName(const std::string &name)
{
    firstName = name;
}

void Patient::setMiddleName(const std::string &name)
{
    middleName = name;
}

void Patient::setLastName(const std::string &name)
{
    lastName = name;
}

const std::string &Patient::getFirstName() const
{
    return firstName;
}

const std::string &Patient::getMiddleName() const
{
    return middleName;
}

const std::string &Patient::getLastName() const
{
    return lastName;
}

int Patient::getRequestTime() const
{
    return requestTime;
}

int Patient::getSeverity() const
{
    return severity;
}

Patient::PatientType Patient::getType() const
{
    return type;
}

int Patient::getNearestHospitalID() const
{
    return nearestHospitalID;
}

void Patient::printDetails() const
{
    std::cout << "First Name: " << firstName << "\n"
              << "Middle Name: " << middleName << "\n"
              << "Last Name: " << lastName << "\n";
}

void Patient::setNearestHospitalID(int ID)
{
    nearestHospitalID = ID;
}