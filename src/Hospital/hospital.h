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
    Node<Car> *headCar;

public:
    Hospital(int hospitalID, int Cars, int SCars, int NCars);
    int getNumberOfPatients(int patientType);
    void addPatient(Patient patientInstance);
    void addCar(Car carInstance);
    bool assignCarToPatient();

    int getHospitalID();
    int getTotalCars();
    int getSpecialCars();
    int getNormalCars();
};

#endif // HOSPITAL_H
