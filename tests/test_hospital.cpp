#include <iostream>
#include "../src/Hospital/hospital.h"
#include "../src/Patient/patient.h"
#include "../src/Car/car.h"

void testHospitalConstructor()
{
    // Test the constructor of the Hospital class
    Hospital hospital(1, 5, 2, 3);
    std::cout << "Hospital ID: " << hospital.getHospitalID() << std::endl;
    std::cout << "Total Cars: " << hospital.getTotalCars() << std::endl;
    std::cout << "Special Cars: " << hospital.getSpecialCars() << std::endl;
    std::cout << "Normal Cars: " << hospital.getNormalCars() << std::endl;
}

void testAddPatient()
{
    // Create a Hospital object
    Hospital hospital(1, 5, 2, 3);
    
    // Create patients
    Patient patient1;
    patient1.setFirstName("John");
    patient1.setLastName("Doe");
    patient1.setPatientType(Patient::SP);  // Special Patient
    hospital.addPatient(patient1);
    
    Patient patient2;
    patient2.setFirstName("Jane");
    patient2.setLastName("Doe");
    patient2.setPatientType(Patient::NP);  // Normal Patient
    hospital.addPatient(patient2);
    
    // Test if the number of patients of each type is correct
    std::cout << "Number of Special Patients: " << hospital.getNumberOfPatients(Patient::SP) << std::endl;
    std::cout << "Number of Normal Patients: " << hospital.getNumberOfPatients(Patient::NP) << std::endl;
}

void testAddCarsAndDequeue()
{
    // Create a Hospital object
    Hospital hospital(1, 5, 2, 3);
    
    // Add cars to the hospital
    hospital.addCars(Car::SC, 100, 2); // Add 2 special cars
    hospital.addCars(Car::NC, 80, 3);   // Add 3 normal cars
    
    // Print car counts before dequeue
    std::cout << "Total Cars before dequeue: " << hospital.getTotalCars() << std::endl;
    std::cout << "Special Cars before dequeue: " << hospital.getSpecialCars() << std::endl;
    std::cout << "Normal Cars before dequeue: " << hospital.getNormalCars() << std::endl;
    
    // Dequeue cars
    hospital.dequeueCar(Car::SC, 1); // Dequeue 1 special car
    
    // Print car counts after dequeue
    std::cout << "Total Cars after dequeue: " << hospital.getTotalCars() << std::endl;
    std::cout << "Special Cars after dequeue: " << hospital.getSpecialCars() << std::endl;
    std::cout << "Normal Cars after dequeue: " << hospital.getNormalCars() << std::endl;
}

void testHospital()
{
    testHospitalConstructor();
    testAddPatient();
    testAddCarsAndDequeue();
}

int main()
{
    std::cout << "Running Hospital tests..." << std::endl;
    testHospital();
    return 0;
}
