#include "hospital.h"

Hospital::Hospital(int ID) :
    hospitalID(ID), 
    headSP(new Queue<Patient*>()), 
    headEP(new PriorityQueue<Patient*>()), 
    headNP(new DerivedQueue<Patient*>()), 
    headSC(new Queue<Car*>()), 
    headNC(new Queue<Car*>()) 
{}

Queue<Patient*>* Hospital::getHeadSP() const { return headSP; }
PriorityQueue<Patient*>* Hospital::getHeadEP() const { return headEP; }
DerivedQueue<Patient*>* Hospital::getHeadNP() const { return headNP; }

Queue<Car*>* Hospital::getHeadSC() const { return headSC; }
Queue<Car*>* Hospital::getHeadNC() const { return headNC; }

void Hospital::addCars(Car::CarType type, int amount)
{
    Queue<Car*>* targetQueue = (type == Car::CarType::SC) ? headSC : headNC;
    for (int i = 0; i < amount; i++)
    {
        Car* newCar = new Car(type, i+1);
        targetQueue->enqueue(newCar);
    }
}

void Hospital::returnCar(Car* carInstance)
{
    // std::cout << "return call" << std::endl;
    switch (carInstance->getCarType())
    {
        case Car::CarType::SC:
            headSC->enqueue(carInstance);
            // std::cout << "A special car has returned to hospital " << hospitalID << std::endl;
            break;
        case Car::CarType::NC:
            headNC->enqueue(carInstance);
            // std::cout << "A normal car has returned to hospital " << hospitalID << std::endl;
            break;
        default:
            std::cout << "RETURNED CAR OF INVALID TYPE!" << std::endl; // this should never trigger
            break;
    }
}

void Hospital::addPatient(Patient* patientInstance, int severity)
{
    switch (patientInstance->getType())
    {
        case Patient::PatientType::NP:
            headNP->enqueue(patientInstance);
            // std::cout << "\n+ Added NP patient_" << patientInstance->getPID() << " to H: " << patientInstance->getNearestHospitalID() << "\n" << std::endl;
            break;
        case Patient::PatientType::SP:
            headSP->enqueue(patientInstance);
            // std::cout << "\n+ Added SP patient_" << patientInstance->getPID() << " to H: " << patientInstance->getNearestHospitalID() << "\n" << std::endl;
            break;
        case Patient::PatientType::EP:
            headEP->enqueue(patientInstance, severity);
            // debugging:
            // if (patientInstance->getPID() == 4)
            // {
            //     std::cout << "w elmos7af da5lt el mosta4fa" << std::endl;
            // }
            // std::cout << "\n+ Added EP patient_" << patientInstance->getPID() << " to H: " << patientInstance->getNearestHospitalID() << "\n" << std::endl;
            break;
        default:
            std::cout << "PATIENT TYPE NOT FOUND!" << std::endl;
            break;
    }
}

int Hospital::getHospitalID()
{
    return hospitalID;
}

int Hospital::getNumberOfPatients(int type)
{
    int count = 0;
    if (type == 0) count = headNP->size();
    else if (type == 1) count = headSP->size();
    else if (type == 2) count = headEP->size();
    else count = headNP->size() + headSP->size() + headEP->size();
    return count;
}

int Hospital::getNumberOfCars(int type)
{
    if (!headSC || !headNC) // Check if queues are initialized
    {
        std::cerr << "Error: Car queues are not initialized!" << std::endl;
        return 0;
    }

    switch (type)
    {
    case 0: // SC
        return headSC->size();
    case 1: // NC
        return headNC->size();
    case 2: // All cars
        return headSC->size() + headNC->size();
    default:
        std::cerr << "NO CAR TYPE MATCHED!" << std::endl;
        return 0;
    }
}

void Hospital::printHospitalDetails()
{
    std::cout << "\n[INFO]" << std::endl;
    std::cout << "Hospital ID: " << hospitalID << std::endl;
    std::cout << "Hospital Patient Lists Details:" << std::endl;
    
    Queue<Patient*> spTempQueue(*headSP);
    Patient* spTemp = new Patient();
    while (spTempQueue.dequeue(spTemp))
    {
        spTemp->printDetails();
    }

    DerivedQueue<Patient*> npTempQueue(*headNP);
    Patient* npTemp = new Patient();
    while (npTempQueue.dequeue(npTemp))
    {
        npTemp->printDetails();
    }

    int severity;
    PriorityQueue<Patient*> epTempQueue(*headEP);
    Patient* epTemp = new Patient();
    while (epTempQueue.dequeue(epTemp, severity))
    {
        epTemp->printDetails();
    }

    // headEP->display();

    std::cout << "\n[SUMMARY]" << std::endl;
    std::cout << "Total Number of Patients:" << std::endl;
    std::cout << "Non-Prioritized Patients: " << getNumberOfPatients(0) << std::endl;
    std::cout << "Standard Prioritized Patients: " << getNumberOfPatients(1) << std::endl;
    std::cout << "Emergency Prioritized Patients: " << getNumberOfPatients(2) << std::endl;
    std::cout << "Total Patients: " << getNumberOfPatients(3) << std::endl << std::endl;
}