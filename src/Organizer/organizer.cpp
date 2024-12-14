#include "organizer.h"

Organizer::Organizer() :
    hospitals(nullptr),
    incomingPatients(new Queue<Patient*>()), 
    waitingPatients(new Queue<Patient*>()), 
    cancelledPatients(new Queue<CancelledRequest>()), 
    OUT(new ExtendedPriorityQueue<Car*>()), 
    BACK(new ExtendedPriorityQueue<Car*>()), 
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

bool Organizer::assignCarToPatient()
{
    for (int i = 0; i < hospitalCount; i++)
    {
        Car* tempSC = new Car();
        Patient* tempSP = new Patient();
        while (hospitals[i].getNumberOfCars(0) > 0 && hospitals[i].getHeadSP()->peek(tempSP))
        {
            hospitals[i].getHeadSP()->dequeue(tempSP);
            hospitals[i].getHeadSC()->dequeue(tempSC);

            tempSC->setCurrentPatient(tempSP);
            tempSC->setCarStatus(Car::CarStatus::ASSIGNED);

            OUT->enqueue(tempSC, tempSP->getPT());
        }
    }

    return true;
}

void Organizer::loadInputData()
{
    std::cout << std::endl << "Loading data to be simulated..." << std::endl << std::endl;

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

            Patient* newPatient = new Patient
            (
                inputQT,
                inputPID,
                inputHID,
                inputDistance,
                inputTypeConverted,
                inputSeverity
            );

            incomingPatients->enqueue(newPatient);
        }
    }

    // Debugging:
    // for (int i = 0; i < hospitalCount; i++) { std::cout << "Hospital " << i+1 << " patients: " << hospitals[i].getNumberOfPatients(3) << std::endl; }

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
            // struct:
            CancelledRequest cancelledRequestInstance;

            cancelledRequestInstance.cTimestep = cTime;
            cancelledRequestInstance.cPID = cPID;
            cancelledRequestInstance.cHID = cHID;

            cancelledPatients->enqueue(cancelledRequestInstance);
        }
    }

    file.close();
}

void Organizer::simulate()
{
    std::cout << std::endl << "Processing simulation..." << std::endl;

    // // debugging:
    // while (!incomingPatients->isEmpty())
    // {
    //     Patient temp;
    //     incomingPatients->dequeue(temp);
    //     temp.printDetails();
    //     std::cout << "\n-----------------------\n" << std::endl;
    // }

    // // debugging:
    // while (!cancelledPatients->isEmpty())
    // {
    //     CancelledRequest temp;
    //     cancelledPatients->dequeue(temp);
    //     std::cout << temp.cTimestep << " " << temp.cPID << " " << temp.cHID << std::endl;
    //     std::cout << "\n-----------------------\n" << std::endl;
    // }

    for (currentTime = 1; currentTime < 100; currentTime++)
    {
        // Beginning of each loop:
        //
        // - We check on cancelledRequests list if there were any
        //   If yes, based on certain criteria:
        //   enqueue the car from OUT list & enqueue it back to
        //   its patient's hospital ID & flag the patient as cancelledRequest
        //   and move the patient to finish list
        //
        // - We check on OUT list if the patient's car PK == currentTime
        //   If yes, dequeue from OUT & enqueue to BACK, else do nothing
        //
        // - We check on BACK list if the patient's car FT == currentTime
        //   If yes:
        //      - send patient to finish list
        //      - dequeue car from BACK
        //      - enqueue the car to the patient's hospital ID
        // - else:
        //      do nothing


        // Actually process the simulation now:


        // Serve waiting patients first:
        // - Add them to their according list inside their hospital
        std::cout << "Timestep: " << currentTime << std::endl;
        Patient* servePatient = new Patient();
        if (incomingPatients->peek(servePatient))
        {
            while (incomingPatients->peek(servePatient))
            {
                if (servePatient->getQT() <= currentTime)
                {
                    incomingPatients->dequeue(servePatient);

                    for (int i = 0; i < hospitalCount; i++)
                    {
                        if (hospitals[i].getHospitalID() == servePatient->getNearestHospitalID())
                        {
                            hospitals[i].addPatient(servePatient, servePatient->getSeverity());
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }

        // Loop over each hospital:
        // - Peek on each list:
        //   - Check if the patient's car type exists
        //      - Assign the patients inside each list their car
        //      - Assignment involves updating the patient's info (times)
        //      - Dequeue a car from the hospital's cars list
        //      - Then dequeuing the patient from their list & set him to that car
        //      - Then enqueue the car to the OUT list
        //   - else:
        //      - do nothing (the patient will remain in their list)
        for (int i = 0; i < hospitalCount; i++)
        {
            Patient* assignSPatient = new Patient();
            while (hospitals[i].getHeadSP()->peek(assignSPatient))
            {
                if (hospitals[i].getNumberOfCars(0) > 0)
                {
                    hospitals[i].getHeadSP()->dequeue(assignSPatient);
                    // assign logic here (special car)
                }
                else
                {
                    break;
                }
            }

            int assignEPriority;
            Patient* assignEPatient = new Patient();
            while (hospitals[i].getHeadEP()->peek(assignEPatient, assignEPriority))
            {
                if (hospitals[i].getNumberOfCars(1) > 0)
                {
                    hospitals[i].getHeadEP()->dequeue(assignEPatient, assignEPriority);
                    // assign logic here (normal car)
                }
                else if (hospitals[i].getNumberOfCars(0) > 0)
                {
                    hospitals[i].getHeadEP()->dequeue(assignEPatient, assignEPriority);
                    // assign logic here (special car)
                }
                else
                {
                    break;
                }
            }

            Patient* assignNPatient = new Patient();
            while (hospitals[i].getHeadNP()->peek(assignNPatient))
            {
                if (hospitals[i].getNumberOfCars(1) > 0)
                {
                    hospitals[i].getHeadNP()->dequeue(assignNPatient);
                    // assign logic here (normal car)
                }
                else
                {
                    break;
                }
            }
        }
    }

    // debugging:
    // for (int i = 0; i < hospitalCount; i++)
    // {
    //     hospitals[i].printHospitalDetails();
    // }

    // debugging:
    // while (!incomingPatients->isEmpty())
    // {
    //     Patient temp;
    //     incomingPatients->dequeue(temp);
    //     temp.printDetails();
    //     std::cout << "\n-----------------------\n" << std::endl;
    // }
}

void Organizer::generateOutput()
{
    // Placeholder for generating output
    std::cout << std::endl << "Simulation complete. Generating output...\n";
}
