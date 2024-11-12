#include "patient.h"

Patient::Patient() : requestTime(0), severity(0), type(NP), nearestHospitalID(0) {}

bool Patient::isEnglishLetter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Patient::isValidName(const std::string &name)
{
    for (char c : name)
    {
        if (!isEnglishLetter(c))
        {
            return false;
        }
    }
    return true;
}

void Patient::getNameInput(std::string &name, const std::string &prompt)
{
    bool valid = false;
    while (!valid)
    {
        std::cout << prompt;
        std::getline(std::cin, name);

        // Check if the name is valid
        if (isValidName(name))
        {
            valid = true;
        }
        else
        {
            std::cout << "Invalid input. Please enter a name using only English letters.\n";
        }
    }
}

void Patient::getFirstName()
{
    getNameInput(firstName, "Enter your first name: ");
}

void Patient::getMiddleName()
{
    getNameInput(middleName, "Enter your middle name: ");
}

void Patient::getLastName()
{
    getNameInput(lastName, "Enter your last name: ");
}

void Patient::printDetails() const
{
    std::cout << "First Name: " << firstName << "\n"
              << "Middle Name: " << middleName << "\n"
              << "Last Name: " << lastName << "\n";
}

void Patient::collectAndDisplayPatientInfo()
{
    getFirstName();
    getMiddleName();
    getLastName();
    printDetails();
}
