#include "organizer.h"

Organizer::Organizer() : 
    hospitals(nullptr), 
    requests(new priQueue<Request>()),
    hospitalCount(0), 
    specialCarSpeed(0), 
    normalCarSpeed(0), 
    currentTime(1) 
{}

Organizer::~Organizer()
{
    // Clean up hospitals list
    Node<Hospital>* currentHospital = hospitals;
    while (currentHospital != nullptr)
    {
        Node<Hospital>* nextHospital = currentHospital->getNext();
        delete currentHospital;
        currentHospital = nextHospital;
    }
    hospitals = nullptr;

    // Clean up requests list
    if (requests != nullptr)
    {
        delete requests;
        requests = nullptr;
    }
}


int Organizer::getValueByMap(int index)
{
    if (index % 11 == 0) return 0; // The index corresponds to a diagonal element in the symmetric matrix

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
    file >> specialCarSpeed >> normalCarSpeed;

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
        newHospital->addCars(Car::NC, normalCarSpeed, NP);
        newHospital->addCars(Car::SC, specialCarSpeed, SP);
        addHospital(newHospital);
    }

    // Node<Hospital>* temp = hospitals; // DEBUGGING
    // while (temp != nullptr)
    // {
    //     std::cout << "Hospital ID #" << temp->getData().getHospitalID() << std::endl;
    //     std::cout << " - Total Cars: " << temp->getData().getTotalCars() << std::endl;
    //     std::cout << " -  Special |  " << temp->getData().getSpecialCars() << std::endl;
    //     std::cout << " -  Normal  |  " << temp->getData().getNormalCars() << std::endl;
    //     std::cout << "---------------------" << std::endl;
    //     temp = temp->getNext();
    // }

    // Node<Hospital>* temp = hospitals; // DEBUGGING
    // while (temp != nullptr)
    // {
    //     Node<Car>* tempCars = temp->getData().getCars();
    //     while (tempCars != nullptr)
    //     {
    //         std::cout << tempCars->getData().getType() << " ";
    //         tempCars = tempCars->getNext();
    //     }
    //     std::cout << std::endl;
    //     temp = temp->getNext();
    // }

    file.close();
}

void Organizer::simulate()
{
    std::ifstream file("../data/input/input_1_2.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file (organizer.cpp / simulate [1])" << std::endl;
        return;
    }

    int calculateSpam = 3 + (hospitalCount * hospitalCount) + (hospitalCount * 2);
    for (int spam, i = 0; i < calculateSpam; i++) {
        file >> spam;
        std::cout << "skipping.." << std::endl;
    }

    int requests;
    file >> requests;

    // i is the pid
    for (int i = 1; i <= requests; i++)
    {
        // Read the following:
        // type - timestep - pid - nearest hospital - distance of nearest hospital - severity
        std::string inputType; // this should be of type 'PatientType' (todo later)
        int timestep;
        int pid;
        int nearestHospital;
        int nearestHospitalDistance;
        int severity;

        if (file >> inputType >> timestep >> pid >> nearestHospital >> nearestHospitalDistance >> severity)
        {
            currentTime = timestep;
            std::cout << "debugging | current timestep: " << currentTime << std::endl;

            // Logic of assigning each patient a car
            // then returning him to the hospital
            //
            // ---------------- BELOW ----------------

            // Check OUT list here first

            // Check BACK list here second

            // Create a patient request based on read data
            Patient newPatient;
            newPatient.setPatientType(inputType);
            newPatient.setNearestHospitalID(nearestHospital);
            Request newRequest(
                newPatient,             // patient
                Car::CarType::NC,       // type
                Car::CarStatus::READY,  // status
                nearestHospitalDistance,// nearestHospitalDistance
                currentTime,            // QT (Queuing Time)
                0,                      // PT (Pickup Time)
                0,                      // WT (Waiting Time)
                0,                      // FT (Finish Time)
                0                       // carBusyTime
            );

            // LOOP: if: for each patient in the priority queue,
            //       their car type exist in their hospital (the amount if > 0)
            //          then ->assignCarToPatient();
            //       else:
            //          do nothing

            // LOOP: if: the current patient (the one we just created above)
            //       their car type exist in their hospital
            //          then ->assignCarToPatient();
            //       else:
            //          enqueue the request to the priority queue
        }
        else
        {
            std::cerr << "Error reading request (organizer.cpp / simulate [2])" << std::endl;
            break;
        }
    }

    // for test - delete later
    int test;
    file >> test;
    std::cout << "\n\n" << test << std::endl << std::endl;

    file.close();
}

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << "Simulation complete. Generating output...\n";
}
