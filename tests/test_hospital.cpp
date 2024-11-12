#include <iostream>
#include "../src/Hospital/hospital.cpp"  // Include the Hospital header

// Function to check if two values are equal
void expectEqual(int actual, int expected, const std::string& testName) {
    if (actual == expected) {
        std::cout << "PASS: " << testName << std::endl;
    } else {
        std::cout << "FAIL: " << testName << " - Expected " << expected << ", but got " << actual << std::endl;
    }
}

// Function to check if a condition is true
void expectTrue(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "PASS: " << testName << std::endl;
    } else {
        std::cout << "FAIL: " << testName << " - Condition was false" << std::endl;
    }
}


// Example test for adding a patient to the hospital
void testAddPatient() {
    Hospital hospital(1);  // Create a hospital object with ID 1
    // NP = 0
    // SP = 1
    // UP = 2
    //             (name, patient-type)
    Patient patient("John Doe", 0);      // Create a normal patient (NP)
    hospital.addPatient(patient);        // Add the patient to the hospital

    // Check if the patient was added correctly
    expectEqual(hospital.getNumberOfPatients(0), 1, "testAddPatient");
}

// Example test for assigning a car
void testAssignCar() {
    Hospital hospital(1);  // Create a hospital object with ID 1
    Car car(10);       // Create a normal car (NC) with speed 10
    hospital.addCar(car);  // Add the car to the hospital

    Patient patient("Jane Smith", 2);  // Create an emergency patient (EP)
    hospital.addPatient(patient);  // Add the patient to the hospital

    bool assigned = hospital.assignCarToPatient();  // Attempt to assign a car
    expectTrue(assigned, "testAssignCar");
}

// Main function to run all tests
int main() {
    std::cout << "Running Tests..." << std::endl;
    testAddPatient();
    testAssignCar();
    return 0;
}