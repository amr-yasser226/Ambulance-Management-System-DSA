#ifndef ORGANIZER_H
#define ORGANIZER_H

#define SIZE 10             // size of array of pointers to hosiptal objects
#include "hospital.h"

class Organizer
{
private:

    Hospital** hospitals= new Hospital*[SIZE]; // Fixed-size array of pointers to Hospital objects (adjust size as needed)
    int hospitalCount;
    int currentTime;

public:
    Organizer();
    void loadInputData();
    void simulate();
    void generateOutput();
    ~Organizer();
};

#endif // ORGANIZER_H
