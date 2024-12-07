#include "hospital.h"

Hospital::Hospital(int ID) :
      hospitalID(ID), 
      headSP(new Queue<Patient>()), 
      headEP(new PriorityQueue<Patient>()), 
      headNP(new DerivedQueue<Patient>()), 
      headSC(new Queue<Car>()), 
      headNC(new Queue<Car>()) 
{}

void Hospital::addCars(Car::CarType type, int amount)
{
    Queue<Car>* targetQueue = (type == Car::CarType::SC) ? headSC : headNC;
    for (int i = 0; i < amount; i++)
    {
        targetQueue->enqueue(Car(type));
    }
}

void Hospital::addPatient(Patient patientInstance, int severity)
{
    switch (patientInstance.getType())
    {
        case Patient::PatientType::NP:
            headNP->enqueue(patientInstance);
            break;
        case Patient::PatientType::SP:
            headSP->enqueue(patientInstance);
            break;
        case Patient::PatientType::EP:
            headEP->enqueue(patientInstance, severity);
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
    Patient temp;
    int trash, count = 0;

    switch (type)
    {
        case 0: // NP
        {
            DerivedQueue<Patient> tempQueue(*headNP);

            while (!tempQueue.isEmpty())
            {
                tempQueue.dequeue(temp);
                count++;
            }
            break;
        }
        case 1: // SP
        {
            Queue<Patient> tempQueue(*headSP);

            while (!tempQueue.isEmpty())
            {
                tempQueue.dequeue(temp);
                count++;
            }
            break;
        }
        case 2: // EP
        {
            PriorityQueue<Patient> tempQueue;
            
            priNode<Patient>* current = headEP->getHead();
            while (current)
            {
                tempQueue.enqueue(current->getItem(trash), trash);
                current = current->getNext();
                count++;
            }
            break;
        }
        case 3: // All patients
            count = getNumberOfPatients(0) + getNumberOfPatients(1) + getNumberOfPatients(2);
            break;
        default:
            std::cout << "NO PATIENT TYPE MATCHED!" << std::endl;
            break;
    }
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
