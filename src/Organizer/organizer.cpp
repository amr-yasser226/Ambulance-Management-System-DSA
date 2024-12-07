#include "organizer.h"

Organizer::Organizer() :
    hospitals(nullptr),
    requests(0),
    cancellations(0),
    hospitalCount(0),
    specialCarSpeed(0),
    normalCarSpeed(0),
    currentTime(0)
{}

Organizer::~Organizer()
{
    if (hospitals != nullptr)
    {
        delete[] hospitals;
        hospitals = nullptr;
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

// bool Organizer::assignCarToPatient(Patient patientInstance)
// {
//     Node<Hospital>* targetHospital = nullptr;

//     int tempNearestHospitalID = patientInstance.getNearestHospitalID();

//     Node<Hospital>* temp = hospitals;
//     while (temp != nullptr)
//     {
//         if (temp->getItem().getHospitalID() == tempNearestHospitalID)
//         {
//             targetHospital = temp;
//             break;
//         }

//         temp = temp->getNext();
//     }

//     if (targetHospital == nullptr) { return false; }

//     int requiredCarType;
//     switch (patientInstance.getType())
//     {
//         case Patient::PatientType::NP:
//             requiredCarType = 1;
//             break;
//         case Patient::PatientType::SP:
//             requiredCarType = 0;
//             break;
//         case Patient::PatientType::EP:
//             requiredCarType = 1;
//             break;
//         default:
//             return false;
//     }

//     if (targetHospital->getItem().getNumberOfCars(requiredCarType) > 0)
//     {
//         // implement assigning logic here based on his car type
//     }
//     else if (patientInstance.getType() == Patient::PatientType::EP && targetHospital->getItem().getNumberOfCars(1) <= 0)
//     {
//         if (targetHospital->getItem().getNumberOfCars(0) > 0)
//         {
//             // implement the same assigning logic here
//             // for this emergency patient but using a Special car
//         }
//     }
//     else
//     {
//         // add this patient to a waiting list

//         // update:
//         //  not a waiting list
//         //  he will just remain in his place
//     }

//     return true;
// }

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

    hospitals = new Hospital[hospitalCount];

    int specialCarsAmount, normalCarsAmount;
    for (int y = 0; y < hospitalCount; y++)
    {
        file >> specialCarsAmount >> normalCarsAmount;

        Hospital newHospital(y+1);

        std::cout << "Before: " << newHospital.getNumberOfCars(0) << " " << newHospital.getNumberOfCars(1) << std::endl;

        newHospital.addCars(Car::CarType::SC, specialCarsAmount);
        newHospital.addCars(Car::CarType::NC, normalCarsAmount);

        std::cout << "After:  " << newHospital.getNumberOfCars(0) << " " << newHospital.getNumberOfCars(1) << std::endl;

        hospitals[y] = newHospital;
        std::cout << "Total cars amount: " << hospitals[y].getNumberOfCars(2) << std::endl;
    }

    std::cout << std::endl;

    file >> requests;

    std::string inputType;
    int inputQT, inputPID, inputHID, inputDistance, inputSeverity;
    int cTime, cPID, cHID;

    for (int i = 0; i < requests; i++)
    {
        if (file >> inputType >> inputQT >> inputPID >> inputHID >> inputDistance >> inputSeverity)
        {
            Patient::PatientType inputTypeConverted;

            if (inputType == "NP")
            {
                inputTypeConverted = Patient::PatientType::NP;
            }
            else if (inputType == "SP")
            {
                inputTypeConverted = Patient::PatientType::SP;
            }
            else if (inputType == "EP")
            {
                inputTypeConverted = Patient::PatientType::EP;
            }
            else
            {
                std::cerr << "Error opening file (organizer.cpp / loadInputData [2])" << std::endl;
                inputTypeConverted = Patient::PatientType::NP;
            }

            Patient newPatient
            (
                inputQT,
                inputPID,
                inputHID,
                inputDistance,
                inputTypeConverted
            );

            for (int i = 0; i < hospitalCount; i++)
            {
                if (hospitals[i].getHospitalID() == inputHID)
                {
                    hospitals[i].addPatient(newPatient, inputSeverity);
                }
            }
        }
    }

    // Debugging:
    for (int i = 0; i < hospitalCount; i++) { std::cout << "Hospital " << i+1 << " patients: " << hospitals[i].getNumberOfPatients(3) << std::endl; }

    if (!(file >> cancellations))
    {
        std::cerr << "Error: Cannot read cancellations amount!" << std::endl;
    }

    // Debugging:
    std::cout << "CANCELLED REQUESTS: " << cancellations << std::endl;

    for (int i = 0; i < cancellations; i++)
    {
        if (file >> cTime >> cPID >> cHID)
        {
            // This will stay untouched until
            // we ask the TA
            // Question:
            // Where will these 3 paramteres be saved?
            // For now, this functionality does not
            // affect our code flow anyway
            std::cout << "cancel request num " << i+1 << std::endl;
        }
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
