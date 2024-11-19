#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include "../Patient/patient.h"
#include "../Car/car.h"

// Simplified Node Class
template <class T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node(T data) : data(data), next(nullptr) {}
    void setData(T d) { data = d; }
    void setNext(Node *n) { next = n; }
    T getData() { return data; }
    Node *getNext() { return next; }
};

class Hospital
{
private:
    int hospitalID;
    int patients;
    Node<Patient> *headPatient;
    int cars;
    Node<Car> *headCar;

public:
    Hospital(int hospitalID);
    int getNumberOfPatients(int patientType);
    void addPatient(Patient patientInstance);
    void addCar(Car carInstance);
    bool assignCarToPatient();
};

#endif // HOSPITAL_H
