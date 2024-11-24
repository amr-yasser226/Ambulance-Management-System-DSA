#include "organizer.h"

Organizer::Organizer() : hospitals(nullptr), hospitalCount(0), SCars(0), NCars(0), currentTime(0) {}

Organizer::~Organizer()
{
    Node<Hospital>* current = hospitals;

    while (current != nullptr)
    {
        Node<Hospital>* next = current->getNext();
        delete current;
        current = next;
    }

    hospitals = nullptr;
}


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

void Organizer::addHospital(Hospital* hospitalInstance)
{
    if (hospitalInstance == nullptr) { return; }

    Node<Hospital>* instance = new Node<Hospital>(*hospitalInstance);
    // Logic of interseting a node to the end of a linkedlist
    if (hospitals == nullptr)
    {
        hospitals = instance;
    }
    else
    {
        Node<Hospital>* temp = hospitals;
        while (temp->getNext() != nullptr) { temp = temp->getNext(); }
        temp->setNext(instance);
    }
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

    // Skip the hospitals distance matrix
    int spam;
    for (int y = 0; y < hospitalCount; y++) { for (int x = 0; x < hospitalCount; x++) { file >> spam; } }
    // Skipped to the beginning of each hospital's cars amount

    // create x number of hospitals based on hospitalCount
    // for each hospital set its required/given data
    // from the input file then add it the hospitals' linkedlist
    int SP, NP;
    for (int y = 1; y < hospitalCount+1; y++)
    {
        file >> SP >> NP;
        Hospital* newHospital = new Hospital(y, SP+NP, SP, NP);
        addHospital(newHospital);
    }

    Node<Hospital>* temp = hospitals; // DEBUGGING
    while (temp != nullptr)
    {
        std::cout << temp->getData().getHospitalID() << std::endl;
        std::cout << temp->getData().getTotalCars() << std::endl;
        std::cout << temp->getData().getSpecialCars() << std::endl;
        std::cout << temp->getData().getNormalCars() << std::endl;
        std::cout << "---------------------" << std::endl;
        temp = temp->getNext();
    }

    file.close();
}

// void Organizer::simulate()
// {
//     while (currentTime < 1000)
//     { // Arbitrary simulation limit, adjust as needed
//         for (int i = 0; i < hospitalCount; i++)
//         {
//             hospitals[i]->assignCarToPatient();
//         }
//         currentTime++;
//     }
// }

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << "Simulation complete. Generating output...\n";
}
