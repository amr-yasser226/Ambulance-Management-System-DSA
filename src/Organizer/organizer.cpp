#include "organizer.h"
#include "../Hospital/hospital.cpp"
#include "../Patient/patient.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Organizer::Organizer() : hospitalCount(0), currentTime(0)
// {
//     for (int i = 0; i < hospitalCount; i++)
//     {
//         hospitals[i] = nullptr;
//     }
// }

// Organizer::~Organizer()
// {

//     for (int i = 0; i < hospitalCount; i++)
//     {
//         delete hospitals[i];
//     }
// }


int Organizer::getValueByMap(int index)
{
    if (index % 11 == 0) return 0; // Means the index is in

    int spam, targetValue = 99, value = -1;

    std::ifstream file("../data/input/input_1_2.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file (organizer.cpp / getValueByMap)" << std::endl;
        return -2;
    }

    for (int i = 0; i < 3; i++) { file >> spam; } // skip to the first actual number in the matrix
    for (int y = 0; y < hospitalCount; y++)
    {
        for (int x = 0; x < hospitalCount && value == -1; x++)
        {
            targetValue = (y+1) * 10 + (x+1);
            if (targetValue == index)
            {
                file >> value;
                y = 9999;
            }
            file >> spam;
        }
    }

    file.close();

    return value;
}

void Organizer::loadInputData()
{
    std::ifstream file("../data/input/input_1_2.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file (organizer.cpp / loadInputData)" << std::endl;
        return;
    }

    // Read first 2 lines
    file >> hospitalCount;
    file >> SCars >> NCars;

    // Reading the hospitals distance matrix

    // to be continued..
    //
    // create x number of hospitals based on hospitalCount
    // for each hospital set its required/given data
    // from the input file
}

void Organizer::simulate()
{
    while (currentTime < 1000)
    { // Arbitrary simulation limit, adjust as needed
        for (int i = 0; i < hospitalCount; i++)
        {
            // hospitals[i]->assignCarToPatient();
        }
        currentTime++;
    }
}

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << "Simulation complete. Generating output...\n";
}
