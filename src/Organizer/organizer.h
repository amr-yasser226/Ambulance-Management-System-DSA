#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "../Hospital/hospital.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Organizer
{
private:
    // Hospital *hospitals[10]; // Fixed-size array of pointers to Hospital objects (adjust size as needed)
    int hospitalCount = 0;
    int SCars = 0, NCars = 0;
    int currentTime = 0;


public:
    // Organizer();
    // ~Organizer();
    
    int getValueByMap(int index); // Example: getValueByMap(12) will return value at row index 0 at column index 1
    //                                        getValueByMap(11) or getValueByMap(33) will return 0 always
    //                                        if return is -1, then index not found
    //                                        if return is -2, then error opening input file
    void loadInputData();
    void simulate();
    void generateOutput();
};

#endif // ORGANIZER_H
