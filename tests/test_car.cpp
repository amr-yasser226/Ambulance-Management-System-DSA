#include "../src/Car/car.h"
#include "../src/Patient/patient.h"
#include <iostream>

int main() {
    // Create a car object
    Car car(Car::SC, 100);

    // Test initial car status and properties
    if (car.getStatus() == Car::READY) {
        std::cout << "Initial car status is READY.\n";
    } else {
        std::cout << "ERROR: Initial car status is not READY.\n";
    }

    if (car.getType() == Car::SC) {
        std::cout << "Car type is SC (Special Car).\n";
    } else {
        std::cout << "ERROR: Car type is not SC.\n";
    }

    if (car.getSpeed() == 100) {
        std::cout << "Car speed is 100.\n";
    } else {
        std::cout << "ERROR: Car speed is not 100.\n";
    }

    if (car.getCurrentPatient() == nullptr) {
        std::cout << "No patient assigned initially.\n";
    } else {
        std::cout << "ERROR: There is an initial patient assigned.\n";
    }

    // Create a patient object
    Patient patient;
    patient.setFirstName("John");
    patient.setMiddleName("Middle");
    patient.setLastName("Doe");
    patient.setPatientType(Patient::SP); // Setting patient type as Special (SP)
    patient.setNearestHospitalID(1); // Example Hospital ID

    // Assign the patient to the car
    // car.assignPatient(&patient);

    // Test car status and current patient after assignment
    if (car.getStatus() == Car::ASSIGNED) {
        std::cout << "Car status is ASSIGNED.\n";
    } else {
        std::cout << "ERROR: Car status is not ASSIGNED.\n";
    }

    if (car.getCurrentPatient() != nullptr && car.getCurrentPatient()->getFirstName() == "John" && 
        car.getCurrentPatient()->getLastName() == "Doe") {
        std::cout << "Patient 'John Doe' successfully assigned to the car.\n";
    } else {
        std::cout << "ERROR: Incorrect patient assigned or patient not assigned.\n";
    }

    // Drop the patient from the car
    car.dropPatient();

    // Test car status and patient after dropping
    if (car.getStatus() == Car::READY) {
        std::cout << "Car status is READY after dropping the patient.\n";
    } else {
        std::cout << "ERROR: Car status is not READY after dropping the patient.\n";
    }

    if (car.getCurrentPatient() == nullptr) {
        std::cout << "No patient assigned after dropping.\n";
    } else {
        std::cout << "ERROR: There is still a patient assigned after dropping.\n";
    }

    // Test normal car functionality
    Car normalCar(Car::NC, 80);
    if (normalCar.getStatus() == Car::READY) {
        std::cout << "Normal car status is READY.\n";
    } else {
        std::cout << "ERROR: Normal car status is not READY.\n";
    }

    if (normalCar.getType() == Car::NC) {
        std::cout << "Normal car type is NC (Normal Car).\n";
    } else {
        std::cout << "ERROR: Normal car type is not NC.\n";
    }

    if (normalCar.getSpeed() == 80) {
        std::cout << "Normal car speed is 80.\n";
    } else {
        std::cout << "ERROR: Normal car speed is not 80.\n";
    }

    std::cout << "Car class tests completed.\n";
    return 0;
}
