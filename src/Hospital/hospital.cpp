#include "hospital.h"

Hospital::Hospital(int hospitalID, int Cars, int SCars, int NCars) : hospitalID(hospitalID), Cars(Cars), SCars(SCars), NCars(NCars), patients(0), headPatient(nullptr), headCar(nullptr) {}

int Hospital::getHospitalID() { return hospitalID; }
int Hospital::getTotalCars() { return Cars; }
int Hospital::getSpecialCars() { return SCars; }
int Hospital::getNormalCars() { return NCars; }

int Hospital::getNumberOfPatients(int patientType)
{
    int count = 0;
    Node<Patient> *temp = headPatient;
    while (temp != nullptr)
    {
        // We first have to convert the enum to int
        // so we are able to compare
        int currentPatientType = static_cast<int>(temp->getData().getType());
        if (currentPatientType == patientType)
        {
            count++;
        }
        temp = temp->getNext();
    }
    return count;
}

void Hospital::addPatient(Patient patientInstance)
{
    Node<Patient>* newPatient = new Node<Patient>(patientInstance);
    newPatient->setNext(headPatient);
    headPatient = newPatient;
    patients++;
}

void Hospital::addCar(Car carInstance)
{
    Node<Car> *newCar = new Node<Car>(carInstance);
    newCar->setNext(headCar);
    headCar = newCar;
    Cars++;
}

bool Hospital::assignCarToPatient()
{
    // Implement logic for assigning cars to patients here
    return false;
}
