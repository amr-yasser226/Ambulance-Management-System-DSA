#include "patient.h"

// Constructor
Patient::Patient() : requestTime(0), severity(0), type(NP), nearestHospitalID(0) {}

// Method to check if a character is an English letter
bool Patient::isEnglishLetter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Method to check if a string is composed only of English letters
bool Patient::isValidName(const std::string &name)
{
    for (char c : name)
    { // Iterate over each character in the string
        if (!isEnglishLetter(c))
        {
            return false; // Return false if any character is not an English letter
        }
    }
    return true; // Return true if all characters are valid
}

// Method to get and validate a name input
void Patient::getNameInput(std::string &name, const std::string &prompt)
{
    bool valid = false;
    while (!valid)
    {
        std::cout << prompt;
        std::getline(std::cin, name); // Read the input into the string

        // Check if the name is valid
        if (isValidName(name))
        {
            valid = true; // Input is valid
        }
        else
        {
            std::cout << "Invalid input. Please enter a name using only English letters.\n";
        }
    }
}

// Methods to get the names from the patient
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

// Method to print patient details
void Patient::printDetails() const
{
    std::cout << "First Name: " << firstName << "\n"
              << "Middle Name: " << middleName << "\n"
              << "Last Name: " << lastName << "\n";
}

// Method to perform all input and output actions in one call
void Patient::collectAndDisplayPatientInfo()
{
    getFirstName();
    getMiddleName();
    getLastName();
    printDetails();
}
