#ifndef UI_H
#define UI_H

#include <iostream>
#include "patient.h"

class UI
{
public:
    void collectPatientInfo(Patient &patient);

private:
    bool isEnglishLetter(char c);
    bool isValidName(const std::string &name);
    void getNameInput(std::string &name, const std::string &prompt);
};

#endif // UI_H
