#include "ui.h"

bool UI::isEnglishLetter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool UI::isValidName(const std::string &name)
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

void UI::getNameInput(std::string &name, const std::string &prompt)
{
    bool valid = false;
    while (!valid)
    {
        std::cout << prompt;
        std::getline(std::cin, name);

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

void UI::collectPatientInfo(Patient &patient)
{
    std::string firstName, middleName, lastName;
    getNameInput(firstName, "Enter your first name: ");
    getNameInput(middleName, "Enter your middle name: ");
    getNameInput(lastName, "Enter your last name: ");

    patient.setFirstName(firstName);
    patient.setMiddleName(middleName);
    patient.setLastName(lastName);

    patient.printDetails();
}
