#include "patient.h"

Patient::Patient() 
    : firstName("")
    , middleName("")
    , lastName("")
    , requestTime(0)
    , severity(0)
    , type(NP)
    , nearestHospitalID(0) 
{}

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

void Patient::setPatientType(std::string type)
{
    if (type == "NP")
    {
        this->type = NP;
    }
    else if (type == "SP")
    {
        this->type = SP;
    }
    else if (type == "EP")
    {
        this->type = EP;
    }
    else
    {
        std::cerr << "Error: Invalid patient type provided." << std::endl;
    }
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