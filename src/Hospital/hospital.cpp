#include <iostream>

class Patient {
    private:
        std::string name;
        int type;
    public:
        Patient(std::string name, int type) : name(name), type(type) {}
        int getType() { return type; }
};

class Car {
    private:
        int speed;
    public:
        Car(int speed) : speed(speed) {}
        int getSpeed() { return speed; }
};

template<class T>
class Node {
private:
    T Data;
    Node* Next = nullptr;
    // Node* Previous = nullptr;

public:
    Node(T data) : Data(data) {}

    void setData(T d) { Data = d; }
    void setNext(Node* N) { Next = N; }
    // void setPrevious(Node* P) { Previous = P; }

    T getData() { return Data; }
    Node* getNext() { return Next; }
    // Node* getPrevious() { return Previous; }
};

class Hospital {
    private:
        int hospitalID;
        //------------------------------
        int patients = 0;
        Node<Patient>* headPatient = nullptr;
        //------------------------------
        int cars = 0;
        Node<Car>* headCar = nullptr;

    public:
        Hospital(int hospitalID) : hospitalID(hospitalID) {}

        int getNumberOfPatients(int patientType) {
            int count = 0;
            Node<Patient>* temp = headPatient;
            while (temp != nullptr) {
                if (temp->getData().getType() == patientType) { count++; }
                temp = temp->getNext();
            }
            return count;
        }

        void addPatient(Patient patientInstance) {
            // insert at the beginning of a linkedlist:
            Node<Patient>* newPatient = new Node<Patient>(patientInstance);
            newPatient->setNext(headPatient);
            headPatient = newPatient;
            patients++;
        }

        void addCar(Car carInstance) {
            Node<Car>* newCar = new Node<Car>(carInstance);
            newCar->setNext(headCar);
            headCar = newCar;
            cars++;
        }

        bool assignCarToPatient() { return false; }
        // based on what the car will be assigned to the patient
        // and:
        //   - what car will be assigned? (its speed)
        //   - to what type of patient? (based on priority?)
};