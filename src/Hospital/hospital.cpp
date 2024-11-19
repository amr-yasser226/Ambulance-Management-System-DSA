#include "hospital.h"

Hospital::Hospital(int hospitalID) : hospitalID(hospitalID), patients(0), headPatient(nullptr), cars(0), headCar(nullptr) {}

int Hospital::getNumberOfPatients(int patientType)
{
    int count = 0;
    Node<Patient> *temp = headPatient;
    while (temp != nullptr)
    {
        if (temp->getData().getType() == patientType)
        {
            count++;
        }
        temp = temp->getNext();
    }
    return count;
}

void Hospital::addPatient(Patient patientInstance)
{
    Node<Patient> *newPatient = new Node<Patient>(patientInstance);
    newPatient->setNext(headPatient);
    headPatient = newPatient;
    patients++;
}

void Hospital::addCar(Car carInstance)
{
    Node<Car> *newCar = new Node<Car>(carInstance);
    newCar->setNext(headCar);
    headCar = newCar;
    cars++;
}

bool Hospital::assignCarToPatient()
{
    // Implement the logic to assign a car to a patient based on their speed and priority
    return false;
}
