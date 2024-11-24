#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include "../Patient/patient.h"
#include "../Car/car.h"
#include "../Data Structures/Node.h"

class Hospital
{
private:
    int hospitalID;
    int Cars, SCars, NCars;
    int patients;
    Node<Patient> *headPatient;
    Node<Car> *headCars; // This includes all cars together | we differentiate between each by car type

public:
    Hospital(int hospitalID, int Cars, int SCars, int NCars);
    int getNumberOfPatients(int patientType);
    void addPatient(Patient patientInstance);
    void addCars(Car::CarType type, int speed, int amount);
    bool assignCarToPatient();

    int getHospitalID();
    int getTotalCars();
    int getSpecialCars();
    int getNormalCars();

    Node<Car>* getCars();
};

#endif // HOSPITAL_H
