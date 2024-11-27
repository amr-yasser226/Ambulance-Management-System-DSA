#include "organizer.h"

Organizer::Organizer() : 
    hospitals(nullptr), 
    requests(new priQueue<Request>()),  // Ensure this is a pointer initialization
    OUT(nullptr),
    BACK(nullptr),
    FINISH(new Stack<Request>()),
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

    // Clean up requests priority queue
    if (requests != nullptr)
    {
        delete requests;
        requests = nullptr;
    }

    // Clean up OUT list
    Node<Request>* currentOut = OUT;
    while (currentOut != nullptr)
    {
        Node<Request>* nextOut = currentOut->getNext();
        delete currentOut;
        currentOut = nextOut;
    }
    OUT = nullptr;

    // Clean up BACK list
    Node<Request>* currentBack = BACK;
    while (currentBack != nullptr)
    {
        Node<Request>* nextBack = currentBack->getNext();
        delete currentBack;
        currentBack = nextBack;
    }
    BACK = nullptr;

    // Clean up FINISH stack
    if (FINISH != nullptr)
    {
        delete FINISH;
        FINISH = nullptr;
    }
}

int Organizer::generateRandomNum(int min, int max)
{
    int num = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);

    num = dist(gen);

    return num;
}

bool Organizer::assignCarToPatient(Request request)
{
    // update the request information:
    // - CarStatus becomes ASSIGNED
    // - QT = stays the same
    // - AT = currentTime
    // - PT = AT + ( request.nearestHospitalDistance / depending on car type set the speed )
    // - WT = PT - QT
    // - FT = PT + ( request.nearestHospitalDistance / depending on car type set the speed )
    // dequeue the car from hospital cars list
    // decrement amount of cars and car's type in the hospital
    // enqueue the car to OUT list

    double speed = (request.type == Car::CarType::SC) ? (specialCarSpeed) : (normalCarSpeed);

    request.status = Car::CarStatus::ASSIGNED;
    request.AT = currentTime;
    request.PT = request.AT + (request.nearestHospitalDistance/(speed));
    request.WT = request.PT - request.QT;
    request.FT = request.PT + (request.nearestHospitalDistance/(speed));

    // stop here

    return true;
}

int Organizer::fetchCarsInHospital(int hospitalID, Car::CarType type)
{
    int carsCount = 0;

    Node<Hospital>* temp = hospitals;

    while (temp != nullptr)
    {
        if (temp->getData().getHospitalID() == hospitalID)
        {
            carsCount = (type == Car::CarType::SC) ? (temp->getData().getSpecialCars()) : (temp->getData().getNormalCars());
            break;
        }

        temp = temp->getNext();
    }

    return carsCount;
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
    std::ifstream file("../data/input/input_1_1.txt");

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
    for (int y = 0; y < hospitalCount * hospitalCount; y++) { file >> spam; }
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

    int requests;
    file >> requests;

    // i is the pid
    for (int i = 1; i <= requests; i++)
    {
        // Read the following:
        // type - timestep - pid - nearest hospital - distance of nearest hospital - severity
        std::string inputType;
        int timestep;
        int pid;
        int nearestHospital;
        int nearestHospitalDistance;
        int severity;

        if (file >> inputType >> timestep >> pid >> nearestHospital >> nearestHospitalDistance >> severity)
        {
            currentTime = timestep;
            std::cout << "debugging | current timestep: " << currentTime << std::endl;

            Car::CarType carType;
            if (inputType == "NP")
            {
                carType = Car::CarType::NC;
            }
            else if (inputType == "SP")
            {
                carType = Car::CarType::SC;
            }
            else if (inputType == "EP")
            {
                carType = Car::CarType::NC;
            }
            else
            {
                std::cerr << "Unknown patient type: " << inputType << " (organizer.cpp / simulate [3])" << std::endl;
                carType = Car::CarType::NC;
            }

            Patient::PatientType patientType;
            if (inputType == "NP")
            {
                patientType = Patient::PatientType::NP;
            }
            else if (inputType == "SP")
            {
                patientType = Patient::PatientType::SP;
            }
            else if (inputType == "EP")
            {
                patientType = Patient::PatientType::EP;
            }
            else
            {
                std::cerr << "Unknown patient type: " << inputType << " (organizer.cpp / simulate [3])" << std::endl;
                carType = Car::CarType::NC;
            }

            // Logic of assigning each patient a car
            // then returning him to the hospital
            //
            // ---------------- BELOW ----------------

            // Check OUT list here first
            
            // Check BACK list here second

            // Create a patient request based on read data
            Patient newPatient;
            newPatient.setPID(pid);
            newPatient.setSeverity(severity);
            newPatient.setPatientType(patientType);
            newPatient.setNearestHospitalID(nearestHospital);

            Request newRequest
            (
                newPatient,                   // patient
                carType,                      // type
                Car::CarStatus::READY,        // status
                nearestHospitalDistance,      // nearestHospitalDistance
                currentTime,                  // QT (Queuing Time)
                0.0,                          // AT (Assignment Time)
                0.0,                          // PT (Pickup Time)
                0.0,                          // WT (Waiting Time)
                0.0,                          // FT (Finish Time)
                0.0                           // carBusyTime
            );

            Organizer::requests->enqueue(newRequest, severity);
        }
    }

    file.close();
}

void Organizer::simulate()
{
    std::ifstream file("../data/input/input_1_1.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file (organizer.cpp / simulate [1])" << std::endl;
        return;
    }

    int calculateSpam = 3 + (hospitalCount * hospitalCount) + (hospitalCount * 2);
    for (int spam, i = 0; i < calculateSpam; i++) { file >> spam; }

    int requests;
    file >> requests;
    std::cout << "REQUESTS || " << requests << std::endl;

    int randomNumber = generateRandomNum(1, 100);

    for (int i = 1; i <= requests; i++)
    {
        if (10 <= randomNumber && randomNumber < 20)
        {
            int priority = 1;
            Request requestInstance;

            std::cout << "R: " << randomNumber << std::endl;
            Organizer::requests->dequeue(requestInstance, priority);
            Organizer::FINISH->push(requestInstance);
        }
        else if (20 <= randomNumber && randomNumber < 25)
        {
            int priority = 2;
            Request requestInstance;

            std::cout << "R: " << randomNumber << std::endl;
            Organizer::requests->dequeue(requestInstance, priority);
            Organizer::FINISH->push(requestInstance);
        }
        else if (30 <= randomNumber && randomNumber < 40)
        {
            int priority = 0;
            Request requestInstance;

            std::cout << "R: " << randomNumber << std::endl;
            Organizer::requests->dequeue(requestInstance, priority);
            Organizer::FINISH->push(requestInstance);
        }
        else if (40 <= randomNumber && randomNumber < 45)
        {
            int priority = 0;
            Request requestInstance;

            std::cout << "R: " << randomNumber << std::endl;
            Organizer::requests->dequeue(requestInstance, priority);
            Organizer::FINISH->push(requestInstance);
        }
        else if (70 <= randomNumber && randomNumber < 75)
        {
            // Move one Ncar from free to out list
        }
        else if (80 <= randomNumber && randomNumber < 90)
        {
            // Move one car from out to back list
        }
        else if (91 <= randomNumber && randomNumber < 95)
        {
            // Move one car from back to "Free" list of its hospital
        }
    }

    file.close();
}

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << "Simulation complete. Generating output...\n";
}
