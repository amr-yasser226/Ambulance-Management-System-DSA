#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include "../Car/car.h"
#include "../Patient/patient.h"
#include "../Data Structures/Queue.h"
#include "../Data Structures/PriorityQueue.h"
#include "../Data Structures/DerivedQueue.h"

class Hospital
{
  private:
    int hospitalID = 0;

    Queue<Patient*> *headSP; // doesn't matter if it's served first or not because it got its own type of cars and cannot be served otherwise.
    PriorityQueue<Patient*>* headEP;
    DerivedQueue<Patient*>* headNP;

    Queue<Car*> *headSC;
    Queue<Car*> *headNC;

  public:
    Hospital() {}
    Hospital(int hospitalID);

    Queue<Patient*>* getHeadSP() const;
    PriorityQueue<Patient*>* getHeadEP() const;
    DerivedQueue<Patient*>* getHeadNP() const;

    Queue<Car*>* getHeadSC() const;
    Queue<Car*>* getHeadNC() const;

    void addCars(Car::CarType type, int amount);
    // loadInputData()
    // this function will use the enqueue function of Queues based on if statements
    // that check car type first, after it finds the car type, it will enqueue to its
    // list x amount of cars

    void addPatient(Patient* patientInstance, int severity);
    // loadInputData()
    // this function will first check the patient's type
    // then will add them to their list accordingly
    // (!) Based on the if statements made, use the enqueue on one of the patient lists

    // this will probably be deleted:
    // void dequeueCar(Car::CarType type, int amount);
    // this function will first check carType and amount to be dequeued
    // then will dequeue them off their list
    // (!) Based on the if statements made, use the dequeue on one of the cars lists

    int getHospitalID();

    int getNumberOfPatients(int type); // get number of patients in any of the 3 lists based on type
    // 0 = NP
    // 1 = SP
    // 2 = EP
    // 3 = All patients

    int getNumberOfCars(int type); // get number of cars in either lists based on the type
    // 0 = SC
    // 1 = NC
    // 2 = All cars

    void printHospitalDetails();
};

#endif
