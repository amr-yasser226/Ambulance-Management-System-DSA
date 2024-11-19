#include "organizer.h"
#include "../Hospital/hospital.cpp"
#include "../Patient/patient.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Organizer::Organizer() : hospitalCount(0), currentTime(0)
{
    for (int i = 0; i < 10; i++)
    {
        hospitals[i] = nullptr;
    }
}

Organizer::~Organizer()
{

    for (int i = 0; i < hospitalCount; i++)
    {
        delete hospitals[i];
    }
}

void Organizer::loadInputData()
{
    std::ifstream file("../input.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file (organizer.cpp)" << std::endl;
        return 1;
    }

    int matrix[150][6];
    int row_count = 0;
    std::string line, line_type;
    
}

void Organizer::simulate()
{
    while (currentTime < 1000)
    { // Arbitrary simulation limit, adjust as needed
        for (int i = 0; i < hospitalCount; i++)
        {
            hospitals[i]->assignCarToPatient();
        }
        currentTime++;
    }
}

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << "Simulation complete. Generating output...\n";
}
