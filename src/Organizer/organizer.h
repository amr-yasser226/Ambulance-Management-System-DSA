#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "hospital.h"

class Organizer
{
private:
    Hospital *hospitals[10];
    int hospitalCount;
    int currentTime;

public:
    Organizer();
    ~Organizer();
    void loadInputData();
    void simulate();
    void generateOutput();
};

#endif // ORGANIZER_H
