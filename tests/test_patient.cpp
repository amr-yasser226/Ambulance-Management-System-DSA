#include <iostream>
#include "../src/Patient/patient.h"

// Function to test the Patient class
void testPatientClass()
{
    // Create an instance of the Patient class
    Patient patient;

    // Set patient information
    patient.setFirstName("John");
    patient.setMiddleName("H.");
    patient.setLastName("Doe");

    // Print patient details to verify correctness
    std::cout << "Testing Patient Class...\n";
    std::cout << "First Name: " << patient.getFirstName() << "\n";
    std::cout << "Middle Name: " << patient.getMiddleName() << "\n";
    std::cout << "Last Name: " << patient.getLastName() << "\n";

    // Additional checks (if needed) for request time, severity, etc.
    std::cout << "Request Time: " << patient.getRequestTime() << "\n";
    std::cout << "Severity: " << patient.getSeverity() << "\n";
    std::cout << "Nearest Hospital ID: " << patient.getNearestHospitalID() << "\n";
}

int main()
{
    std::cout << "Running Tests for Patient Class...\n";
    testPatientClass();
    return 0;
}
