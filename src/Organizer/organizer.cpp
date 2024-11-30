#include "organizer.h"

Organizer::Organizer() :
    hospitals(nullptr),
    hospitalCount(0),
    specialCarSpeed(0),
    normalCarSpeed(0),
    currentTime(0)
{}

Organizer::~Organizer() 
{
    Node<Hospital>* current = hospitals;

    while (current != nullptr)
    {
        Node<Hospital>* temp = current;
        current = current->getNext();
        delete &temp->getItem();
        delete temp;
    }
}

int Organizer::getValueByMap(int index)
{
    if (index % 11 == 0) return 0; // The index corresponds to a diagonal element in the symmetric matrix

    int spam, targetValue = 99, value = -1;

    std::ifstream file("../data/input/input_1_1.txt");

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
    // Logic of interseting a node to the end of a linkedlist

    Node<Hospital>* instance = new Node<Hospital>(*hospitalInstance);

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

bool Organizer::assignCarToPatient(Patient patientInstance)
{
    Node<Hospital>* targetHospital = nullptr;

    int tempNearestHospitalID = patientInstance.getNearestHospitalID();

    Node<Hospital>* temp = hospitals;
    while (temp != nullptr)
    {
        if (temp->getItem().getHospitalID() == tempNearestHospitalID)
        {
            targetHospital = temp;
            break;
        }

        temp = temp->getNext();
    }

    if (targetHospital == nullptr) { return false; }

    int requiredCarType;
    switch (patientInstance.getType())
    {
        case Patient::PatientType::NP:
            requiredCarType = 1;
            break;
        case Patient::PatientType::SP:
            requiredCarType = 0;
            break;
        case Patient::PatientType::EP:
            requiredCarType = 1;
            break;
        default:
            return false;
    }

    if (targetHospital->getItem().getNumberOfCars(requiredCarType) > 0)
    {
        // implement assigning logic here based on his car type
    }
    else if (patientInstance.getType() == Patient::PatientType::EP && targetHospital->getItem().getNumberOfCars(1) <= 0)
    {
        if (targetHospital->getItem().getNumberOfCars(0) > 0)
        {
            // implement the same assigning logic here
            // for this emergency patient but using a Special car
        }
    }
    else
    {
        // add this patient to a waiting list
    }

    return true;
}

void Organizer::loadInputData()
{
    std::ifstream file("../data/input/input_1_1.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file (organizer.cpp / loadInputData [1])" << std::endl;
        return;
    }

    // Read first 2 lines
    file >> hospitalCount;
    file >> specialCarSpeed >> normalCarSpeed;

    // Skip the hospitals distance matrix
    int spam;
    for (int y = 0; y < hospitalCount * hospitalCount; y++) { file >> spam; }
    // Skipped to the beginning of each hospital's cars amount

    // create x number of hospitals based on hospitalCount
    // for each hospital set its required/given data
    // from the input file then add it the hospitals' linkedlist
    int specialCarsAmount, normalCarsAmount;
    for (int y = 1; y < hospitalCount+1; y++)
    {
        file >> specialCarsAmount >> normalCarsAmount;
        Hospital* newHospital = new Hospital(y);
        newHospital->addCars(Car::CarType::SC, specialCarsAmount);
        newHospital->addCars(Car::CarType::NC, normalCarsAmount);
        addHospital(newHospital);
    }

    file.close();
}

void Organizer::simulate()
{
    std::cout << "Processing simulation..." << std::endl;
}

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << "Simulation complete. Generating output...\n";
}
