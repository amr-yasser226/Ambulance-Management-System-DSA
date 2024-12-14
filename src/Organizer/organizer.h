#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "../Car/car.h"
#include "../Patient/patient.h"
#include "../Hospital/hospital.h"
#include "../Data Structures/Queue.h"
#include "../Data Structures/ExtendedPriorityQueue.h"
#include "../Data Structures/CancelledRequest.h"

#include <iostream>
#include <fstream>
#include <string>

class Organizer
{
private:
    Hospital *hospitals = new Hospital[hospitalCount];

    Queue<Patient*> *incomingPatients;
    Queue<CancelledRequest> *cancelledPatients;
    Queue<Patient*> *finishedPatients;

    ExtendedPriorityQueue<Car*> *OUT;
    ExtendedPriorityQueue<Car*> *BACK;



    double specialCarSpeed = 0.0,
           normalCarSpeed = 0.0;

    int requests = 0,
        cancellations = 0,
        hospitalCount = 0,
        currentTime = 0;

public:
    Organizer();
    ~Organizer();

    // This function will be used for the bonus (or deleted entirely)
    int getValueByMap(int index);               
    // Example: getValueByMap(12) will return value at row index 0 at column index 1
    //          getValueByMap(11) or getValueByMap(33) will return 0 always
    //          if return is -1, then index not found
    //          if return is -2, then error opening input file

    bool assignCarToPatient();
    // This should go to the car of the patient's request type in the required hospital (we get the required hospital from the patientInstance's nearestHospitalID)
    // then assign it a patient using setCurrentPatient(Patient patientInstance) <-- this function is in car class
    // - Now, it will be holding a patient
    // then dequeue that car from its hospital cars and enqueue it to OUT list in organizer (OUT list not created in organizer yet)

    int fetchPatientsInHospital(int hospitalID, int type);
    int fetchCarsInHospital(int hospitalID, int type);

    void loadInputData();
    void simulate();
    void generateOutput();
};

#endif // ORGANIZER_H
