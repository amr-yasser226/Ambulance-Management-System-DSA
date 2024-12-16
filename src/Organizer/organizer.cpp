#include "organizer.h"

Organizer::Organizer(int mode) :
    matrix(nullptr),
    hospitals(nullptr),
    incomingPatients(new Queue<Patient*>()), 
    cancelledPatients(new LinkedList<CancelledRequest>()), 
    finishedPatients(new LinkedList<FinishedRequest>()), 
    OUT(new ExtendedPriorityQueue<Car*>()), 
    BACK(new ExtendedPriorityQueue<Car*>()), 
    specialCarSpeed(0.0),
    normalCarSpeed(0.0),
    requests(0),
    cancellations(0),
    hospitalCount(0),
    currentTime(0),
    mode(mode)
{}

Organizer::Organizer() :
    matrix(nullptr),
    hospitals(nullptr),
    incomingPatients(new Queue<Patient*>()), 
    cancelledPatients(new LinkedList<CancelledRequest>()), 
    finishedPatients(new LinkedList<FinishedRequest>()), 
    OUT(new ExtendedPriorityQueue<Car*>()), 
    BACK(new ExtendedPriorityQueue<Car*>()), 
    specialCarSpeed(0.0),
    normalCarSpeed(0.0),
    requests(0),
    cancellations(0),
    hospitalCount(0),
    currentTime(0),
    mode(0)
{}

Organizer::~Organizer()
{
    if (matrix != nullptr)
    {
        for (int i = 0; i < hospitalCount; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }

    if (hospitals != nullptr)
    {
        delete[] hospitals;
        hospitals = nullptr;
    }
}

int Organizer::getMinValue(int array[], int size) {
    int minValue = array[0];
    
    for (int i = 1; i < size; i++) {
        if (array[i] < minValue) {
            minValue = array[i];
        }
    }
    
    return minValue;
}

int Organizer::fetchPatientsInHospital(int hospitalID, int type)
{
    return hospitals[hospitalID - 1].getNumberOfPatients(type);
}

int Organizer::fetchCarsInHospital(int hospitalID, int type)
{
    return hospitals[hospitalID - 1].getNumberOfCars(type);
}

bool Organizer::isRequestCancelled(Car* checkCar)
{
    CancelledRequest tempCR;
    Patient* tempPatient = checkCar->getCurrentPatient();
    Node<CancelledRequest>* CR = cancelledPatients->getHead();

    // According to project rules only normal patient can cancel
    // even though I could let other type of patients cancel too
    //
    if (tempPatient->getType() == Patient::PatientType::NP)
    {
        for (int i = 0; CR != nullptr; i++)
        {
            tempCR = CR->getItem();

            if (tempCR.cTimestep < tempPatient->getPT() && tempCR.cPID == tempPatient->getPID())
            {
                std::cout << "[!] Patient " << tempPatient->getPID() << " has cancelled their request!   [CANCELLED]" << std::endl;
                return true;
            }

            CR = CR->getNext();
        }
    }

    return false;
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

void Organizer::loadInputData()
{
    // std::cout << std::endl << "Loading data to be simulated..." << std::endl << std::endl;

    std::ifstream file("../data/input/input_1_1.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file (organizer.cpp / loadInputData [1])" << std::endl;
        return;
    }

    // Read first 2 lines
    file >> hospitalCount;
    file >> specialCarSpeed >> normalCarSpeed;

    matrix = new int*[hospitalCount];
    hospitals = new Hospital[hospitalCount];

    // Read the matrix
    for (int y = 0; y < hospitalCount; y++)
    {
        matrix[y] = new int[hospitalCount];

        for (int x = 0; x < hospitalCount; x++)
        {
            file >> matrix[y][x];
        }
    }

    // debugging:
    // for (int y = 0; y < hospitalCount; y++)
    // {
    //     for (int x = 0; x < hospitalCount; x++)
    //     {
    //         std::cout << matrix[y][x] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // create x number of hospitals based on hospitalCount
    // for each hospital set its required/given data
    // from the input file then add it the hospitals' dynamic array
    int specialCarsAmount, normalCarsAmount;
    for (int y = 0; y < hospitalCount; y++)
    {
        file >> specialCarsAmount >> normalCarsAmount;

        Hospital newHospital(y+1);

        // std::cout << "Before: " << newHospital.getNumberOfCars(0) << " " << newHospital.getNumberOfCars(1) << std::endl;

        newHospital.addCars(Car::CarType::SC, specialCarsAmount);
        newHospital.addCars(Car::CarType::NC, normalCarsAmount);

        // std::cout << "After:  " << newHospital.getNumberOfCars(0) << " " << newHospital.getNumberOfCars(1) << std::endl;

        hospitals[y] = newHospital;
        // std::cout << "Total cars amount: " << hospitals[y].getNumberOfCars(2) << std::endl;
    }

    file >> requests;

    std::string inputType;
    int inputQT, inputPID, inputHID, inputDistance, inputSeverity;
    int cPID, cHID;
    double cTime;

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
    // std::cout << "CANCELLED REQUESTS: " << cancellations << std::endl;

    for (int i = 0; i < cancellations; i++)
    {
        if (file >> cTime >> cPID >> cHID)
        {
            // struct:
            CancelledRequest cancelledRequestInstance;

            cancelledRequestInstance.cTimestep = cTime;
            cancelledRequestInstance.cPID = cPID;
            cancelledRequestInstance.cHID = cHID;

            cancelledPatients->insertLast(cancelledRequestInstance);
        }
    }

    file.close();
}

void Organizer::simulate()
{
    // std::cout << std::endl << "Processing simulation..." << std::endl;

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

    for (currentTime = 1; currentTime < 150; currentTime++)
    {
        // std::cout << "Timestep: " << currentTime << std::endl;
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
        
        // Move from OUT to BACK
        double outCompareTime = 0.0;
        Car* outToBackCar = new Car();
        if (OUT->peek(outToBackCar, outCompareTime))
        {
            while (OUT->peek(outToBackCar, outCompareTime))
            {
                if (currentTime >= outCompareTime)
                {
                    // move logic here (before u move check if it is cancelled first)
                    if (!isRequestCancelled(outToBackCar))
                    {
                        OUT->dequeue(outToBackCar, outCompareTime);
                        outToBackCar->setCarStatus(Car::CarStatus::LOADED);

                        // TO CHECK THE PT & FT ONLY ONLY ONLY
                        //
                        // if (outToBackCar->getCurrentPatient()->getType() == Patient::PatientType::EP)
                        // {
                        //     std::cout << "EP: " << outToBackCar->getCurrentPatient()->getPID() << std::endl;
                        //     std::cout << outToBackCar->getCurrentPatient()->getPT() << std::endl; // debugging
                        //     std::cout << outToBackCar->getCurrentPatient()->getFT() << std::endl; // debugging
                        // }
                        // else if (outToBackCar->getCurrentPatient()->getType() == Patient::PatientType::SP)
                        // {
                        //     std::cout << "SP: " << outToBackCar->getCurrentPatient()->getPID() << std::endl;
                        //     std::cout << outToBackCar->getCurrentPatient()->getPT() << std::endl; // debugging
                        //     std::cout << outToBackCar->getCurrentPatient()->getFT() << std::endl; // debugging
                        // }
                        // else
                        // {
                        //     std::cout << "NP: " << outToBackCar->getCurrentPatient()->getPID() << std::endl;
                        //     std::cout << outToBackCar->getCurrentPatient()->getPT() << std::endl; // debugging
                        //     std::cout << outToBackCar->getCurrentPatient()->getFT() << std::endl; // debugging
                        // }

                        BACK->enqueue(outToBackCar, outToBackCar->getCurrentPatient()->getFT());
                    }
                    else
                    {
                        // cancellation protocol
                        OUT->dequeue(outToBackCar, outCompareTime);

                        Patient* CPatient = outToBackCar->getCurrentPatient();
                        CPatient->setCancelled();

                        FinishedRequest FR;
                        FR.PID = CPatient->getPID();
                        FR.Severity = CPatient->getSeverity();
                        FR.nearestHospitalID = CPatient->getNearestHospitalID();
                        FR.nearestHospitalDistance = CPatient->getNearestHospitalDistance();
                        FR.type = (CPatient->getType() == Patient::PatientType::EP) ? 2 : (CPatient->getType() == Patient::PatientType::SP) ? 1 : 0;
                        FR.QT = CPatient->getQT();
                        FR.AT = CPatient->getAT();
                        FR.PT = CPatient->getPT();
                        FR.WT = CPatient->getWT();
                        FR.FT = CPatient->getFT();
                        FR.carBusyTime = CPatient->getCarBusyTime();

                        finishedPatients->insertLast(FR);

                        outToBackCar->clearRidingPatient();
                        outToBackCar->setCarStatus(Car::CarStatus::READY);

                        // return the car back to its hospital
                        for (int i = 0; i < hospitalCount; i++)
                        {
                            if (hospitals[i].getHospitalID() == FR.nearestHospitalID)
                            {
                                hospitals[i].returnCar(outToBackCar);
                            }
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }

        // Move from BACK to FINISH
        double backCompareTime = 0.0;
        Car* backToHospitalCar = new Car();
        if (BACK->peek(backToHospitalCar, backCompareTime))
        {
            while (BACK->peek(backToHospitalCar, backCompareTime))
            {
                if (currentTime >= backCompareTime)
                {
                    // move logic here

                    BACK->dequeue(backToHospitalCar, backCompareTime);

                    Patient* finishedPatient = backToHospitalCar->getCurrentPatient();
                    // std::cout << "[+] Patient " << finishedPatient->getPID() << " has arrived to hospital " << finishedPatient->getNearestHospitalID() << " at timestep: " << currentTime << "." << std::endl;

                    FinishedRequest FR;
                    FR.PID = finishedPatient->getPID();
                    FR.Severity = finishedPatient->getSeverity();
                    FR.nearestHospitalID = finishedPatient->getNearestHospitalID();
                    FR.nearestHospitalDistance = finishedPatient->getNearestHospitalDistance();
                    FR.type = (finishedPatient->getType() == Patient::PatientType::EP) ? 2 : (finishedPatient->getType() == Patient::PatientType::SP) ? 1 : 0;
                    FR.QT = finishedPatient->getQT();
                    FR.AT = finishedPatient->getAT();
                    FR.PT = finishedPatient->getPT();
                    FR.WT = finishedPatient->getWT();
                    FR.FT = finishedPatient->getFT();
                    FR.carBusyTime = finishedPatient->getCarBusyTime();

                    finishedPatients->insertLast(FR);

                    backToHospitalCar->clearRidingPatient();
                    backToHospitalCar->setCarStatus(Car::CarStatus::READY);

                    // return the car back to its hospital
                    for (int i = 0; i < hospitalCount; i++)
                    {
                        if (hospitals[i].getHospitalID() == FR.nearestHospitalID)
                        {
                            hospitals[i].returnCar(backToHospitalCar);
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }


        // Actually process the simulation now:


        // Serve patients of same timestep in incomingPatients
        // Send each one to their hospital
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
                        // EPatients have a special case that we check on their hospital's cars
                        // if they exist then send the patient to his hospital normally, if no cars found:
                        //      - Loop on all hospitals & serve him the one with least
                        //      - EPatients in queue
                        //          if multiple ones have same amount of EPatients or
                        //          their EPatients in queue are more than his initial hospital
                        //              - Serve him the hospital nearest to his current hospital

                        if (servePatient->getType() == Patient::PatientType::EP)
                        {
                            //  [4, 20, 20, 11, 4, 16]
                            //
                            // if min is repeated
                            //      if min < yourHospital
                            //          pick one with nearest...
                            //      else
                            //          pick your hospital
                            // else
                            // (which means min is not repeated)
                            //      if min < yourHospital
                            //          pick min hospital ID
                            //      else
                            //          pick your hospital
                        }

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

        // std::cout << "--------------------------> TIMESTEP: " << currentTime << " EP COUNT IN HOS-3: " << fetchPatientsInHospital(3, 2) << std::endl;

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
            double AT = 0.0, PT = 0.0, WT = 0.0, FT = 0.0, CBT = 0.0;

            int assignEPriority;
            Patient* assignEPatient = new Patient();
            while (hospitals[i].getHeadEP()->peek(assignEPatient, assignEPriority))
            {
                if (hospitals[i].getNumberOfCars(1) > 0)
                {
                    // assign logic here (normal car)

                    Car* assignNCar = new Car();

                    hospitals[i].getHeadEP()->dequeue(assignEPatient, assignEPriority);
                    hospitals[i].getHeadNC()->dequeue(assignNCar);

                    AT = currentTime;
                    PT = AT + (assignEPatient->getNearestHospitalDistance() / normalCarSpeed);
                    WT = PT - assignEPatient->getQT();
                    FT = PT + (assignEPatient->getNearestHospitalDistance() / normalCarSpeed);
                    CBT = FT - AT;

                    assignEPatient->setAT(AT);
                    assignEPatient->setPT(PT);
                    assignEPatient->setWT(WT);
                    assignEPatient->setFT(FT);
                    assignEPatient->setCarBusyTime(CBT);

                    assignNCar->setCurrentPatient(assignEPatient);
                    assignNCar->setCarStatus(Car::CarStatus::ASSIGNED);

                    // BLOCK
                    // if (assignNCar->getCurrentPatient()->getType() == Patient::PatientType::EP)
                    // {
                    //     std::cout << "EP: " << assignNCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignNCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignNCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else if (assignNCar->getCurrentPatient()->getType() == Patient::PatientType::SP)
                    // {
                    //     std::cout << "SP: " << assignNCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignNCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignNCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else
                    // {
                    //     std::cout << "NP: " << assignNCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignNCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignNCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }

                    OUT->enqueue(assignNCar, PT);
                    // std::cout << "Car from hospital " << i+1 << " is going for patient " << assignNCar->getCurrentPatient()->getPID() << " at timestep " << currentTime << std::endl;
                }
                else if (hospitals[i].getNumberOfCars(0) > 0)
                {
                    // assign logic here (special car)

                    Car* assignSCar = new Car();

                    hospitals[i].getHeadEP()->dequeue(assignEPatient, assignEPriority);
                    hospitals[i].getHeadSC()->dequeue(assignSCar);

                    AT = currentTime;
                    PT = AT + (assignEPatient->getNearestHospitalDistance() / specialCarSpeed);
                    WT = PT - assignEPatient->getQT();
                    FT = PT + (assignEPatient->getNearestHospitalDistance() / specialCarSpeed);
                    CBT = FT - AT;

                    assignEPatient->setAT(AT);
                    assignEPatient->setPT(PT);
                    assignEPatient->setWT(WT);
                    assignEPatient->setFT(FT);
                    assignEPatient->setCarBusyTime(CBT);

                    assignSCar->setCurrentPatient(assignEPatient);
                    assignSCar->setCarStatus(Car::CarStatus::ASSIGNED);

                    // BLOCK
                    // if (assignSCar->getCurrentPatient()->getType() == Patient::PatientType::EP)
                    // {
                    //     std::cout << "EP: " << assignSCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignSCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignSCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else if (assignSCar->getCurrentPatient()->getType() == Patient::PatientType::SP)
                    // {
                    //     std::cout << "SP: " << assignSCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignSCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignSCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else
                    // {
                    //     std::cout << "NP: " << assignSCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignSCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignSCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }

                    OUT->enqueue(assignSCar, PT);
                    // std::cout << "Car from hospital " << i+1 << " is going for patient " << assignSCar->getCurrentPatient()->getPID() << " at timestep " << currentTime << std::endl;
                }
                else
                {
                    break;
                }
            }

            Patient* assignSPatient = new Patient();
            while (hospitals[i].getHeadSP()->peek(assignSPatient))
            {
                if (hospitals[i].getNumberOfCars(0) > 0)
                {
                    // assign logic here (special car)

                    Car* assignSCar = new Car();

                    hospitals[i].getHeadSP()->dequeue(assignSPatient);
                    hospitals[i].getHeadSC()->dequeue(assignSCar);

                    AT = currentTime;
                    PT = AT + (assignSPatient->getNearestHospitalDistance() / specialCarSpeed);
                    WT = PT - assignSPatient->getQT();
                    FT = PT + (assignSPatient->getNearestHospitalDistance() / specialCarSpeed);
                    CBT = FT - AT;

                    assignSPatient->setAT(AT);
                    assignSPatient->setPT(PT);
                    assignSPatient->setWT(WT);
                    assignSPatient->setFT(FT);
                    assignSPatient->setCarBusyTime(CBT);

                    assignSCar->setCurrentPatient(assignSPatient);
                    assignSCar->setCarStatus(Car::CarStatus::ASSIGNED);

                    // BLOCK
                    // if (assignSCar->getCurrentPatient()->getType() == Patient::PatientType::EP)
                    // {
                    //     std::cout << "EP: " << assignSCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignSCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignSCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else if (assignSCar->getCurrentPatient()->getType() == Patient::PatientType::SP)
                    // {
                    //     std::cout << "SP: " << assignSCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignSCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignSCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else
                    // {
                    //     std::cout << "NP: " << assignSCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignSCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignSCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }

                    OUT->enqueue(assignSCar, PT);
                    // std::cout << "Car from hospital " << i+1 << " is going for patient " << assignSCar->getCurrentPatient()->getPID() << " at timestep " << currentTime << std::endl;
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
                    // assign logic here (normal car)

                    Car* assignNCar = new Car();

                    hospitals[i].getHeadNP()->dequeue(assignNPatient);
                    hospitals[i].getHeadNC()->dequeue(assignNCar);

                    AT = currentTime;
                    PT = AT + (assignNPatient->getNearestHospitalDistance() / normalCarSpeed);
                    WT = PT - assignNPatient->getQT();
                    FT = PT + (assignNPatient->getNearestHospitalDistance() / normalCarSpeed);
                    CBT = FT - AT;

                    assignNPatient->setAT(AT);
                    assignNPatient->setPT(PT);
                    assignNPatient->setWT(WT);
                    assignNPatient->setFT(FT);
                    assignNPatient->setCarBusyTime(CBT);

                    assignNCar->setCurrentPatient(assignNPatient);
                    assignNCar->setCarStatus(Car::CarStatus::ASSIGNED);

                    // BLOCK
                    // if (assignNCar->getCurrentPatient()->getType() == Patient::PatientType::EP)
                    // {
                    //     std::cout << "EP: " << assignNCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignNCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignNCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else if (assignNCar->getCurrentPatient()->getType() == Patient::PatientType::SP)
                    // {
                    //     std::cout << "SP: " << assignNCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignNCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignNCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }
                    // else
                    // {
                    //     std::cout << "NP: " << assignNCar->getCurrentPatient()->getPID() << std::endl;
                    //     std::cout << assignNCar->getCurrentPatient()->getPT() << std::endl; // debugging
                    //     std::cout << assignNCar->getCurrentPatient()->getFT() << std::endl; // debugging
                    // }

                    OUT->enqueue(assignNCar, PT);
                    // std::cout << "Car from hospital " << i+1 << " is going for patient " << assignNCar->getCurrentPatient()->getPID() << " at timestep " << currentTime << std::endl;
                }
                else
                {
                    break;
                }
            }
        }

        // debugging:
        // while (!BACK->isEmpty())
        // {
        //     double pri;
        //     Car* test = new Car();
        //     OUT->dequeue(test, pri);
        //     Patient* ptest = test->getCurrentPatient();
        //     std::cout << "Patient: " << ptest->getPID() << std::endl;
        // }
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

std::string Organizer::generateFileName()
{
    std::time_t now = std::time(0);
    std::tm *localTime = std::localtime(&now);

    // Format: output_DD_MM_YYYY_HH_MM
    std::string fileName = "output_" +
                            std::to_string(localTime->tm_mday) + "_" +
                            std::to_string(localTime->tm_mon + 1) + "_" +
                            std::to_string(localTime->tm_year + 1900) + "_" +
                            std::to_string(localTime->tm_hour) + "_" +
                            std::to_string(localTime->tm_min);

    return fileName;
}

void Organizer::generateOutput()
{
    const std::string folderPath = "../data/output/";

    std::string command = "mkdir -p " + folderPath;
    std::system(command.c_str());

    std::string fileName = folderPath + generateFileName() + ".txt";

    std::ofstream outFile(fileName);

    if (!outFile)
    {
        std::cerr << "Error: Cannot create the file!" << std::endl;
        return;
    }

    outFile << "FT  PID QT  WT" << std::endl;

    // std::cout << "SIZE: " << finishedPatients->size() << std::endl;

    int FRcount = 0;
    int EPcount = 0;
    int SPcount = 0;
    int NPcount = 0;

    int allCars = 0;
    int SCars = 0;
    int NCars = 0;

    for (int i = 1; i <= hospitalCount; i++)
    {
        allCars += fetchCarsInHospital(i, 2);
        SCars += fetchCarsInHospital(i, 0);
        NCars += fetchCarsInHospital(i, 1);
    }

    FinishedRequest tempFR;
    Node<FinishedRequest>* FR = finishedPatients->getHead();

    for (int i = 0; FR != nullptr; i++)
    {
        FRcount++;
        if (tempFR.type == 2) { EPcount++; }
        if (tempFR.type == 1) { SPcount++; }
        if (tempFR.type == 0) { NPcount++; }
        tempFR = FR->getItem();
        outFile << tempFR.FT << " " << tempFR.PID << " " << tempFR.QT << " " << tempFR.WT << std::endl;
        FR = FR->getNext();
    }

    outFile << std::endl;
    outFile << "Patients: " << FRcount << " [NP: " << NPcount << ", SP: " << SPcount << ", EP: " << EPcount << "]" << std::endl;
    outFile << "Hospitals: " << hospitalCount << std::endl;
    outFile << "Cars: " << allCars << " [SCars: " << SCars << ", NCars: " << NCars << "]" << std::endl;

    outFile.close();

    // std::cout << std::endl << "Data has been written to file: " << fileName << std::endl;
}
