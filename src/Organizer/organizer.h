#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "../Car/car.h"
#include "../Patient/patient.h"
#include "../Hospital/hospital.h"
#include "../Data Structures/Node.h"
#include "../Data Structures/Queue.h"
#include "../Data Structures/LinkedList.h"
#include "../Data Structures/FinishedRequest.h"
#include "../Data Structures/CancelledRequest.h"
#include "../Data Structures/ExtendedPriorityQueue.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <ctime>

class Organizer
{
private:

    int **matrix = new int*[2];
    Hospital *hospitals = new Hospital[hospitalCount];

    Queue<Patient*> *incomingPatients;
    LinkedList<CancelledRequest> *cancelledPatients;
    LinkedList<FinishedRequest> *finishedPatients;

    ExtendedPriorityQueue<Car*> *OUT;
    ExtendedPriorityQueue<Car*> *BACK;

    double specialCarSpeed = 0.0,
            normalCarSpeed = 0.0;

    int requests = 0,
        cancellations = 0,
        hospitalCount = 0,
        currentTime = 0,
        mode = 0;

public:
    Organizer();
    Organizer(int mode);
    ~Organizer();

    // This function will be used for the bonus (or deleted entirely)
    int getValueByMap(int index);               
    // Example: getValueByMap(12) will return value at row index 0 at column index 1
    //          getValueByMap(11) or getValueByMap(33) will return 0 always
    //          if return is -1, then index not found
    //          if return is -2, then error opening input file

    // bool assignCarToPatient();
    // This should go to the car of the patient's request type in the required hospital (we get the required hospital from the patientInstance's nearestHospitalID)
    // then assign it a patient using setCurrentPatient(Patient patientInstance) <-- this function is in car class
    // - Now, it will be holding a patient
    // then dequeue that car from its hospital cars and enqueue it to OUT list in organizer (OUT list not created in organizer yet)

    bool isRequestCancelled(Car* checkCar);
    // if return 0, meaning not cancelled
    // if return number between 1 & hospitalCount
    // - then the request will be cancelled
    // - and that number represents the hospital
    // - the car will return to

    int checkNearestHospital(Patient* thePatient);
    int getMinValue(int array[], int size);

    int fetchPatientsInHospital(int hospitalID, int type);
    int fetchCarsInHospital(int hospitalID, int type);

    std::string generateFileName();

    void loadInputData();
    void simulate();
    void generateOutput();
};

#endif // ORGANIZER_H
