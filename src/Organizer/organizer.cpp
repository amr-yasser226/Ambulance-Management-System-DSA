#include "organizer.h"
#include <iostream>

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
    // Placeholder for loading input data
    // Initialize hospitals and load data
}

void Organizer::simulate()
{
    while (currentTime < 1000)
    {
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
