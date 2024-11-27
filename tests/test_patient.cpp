#include <iostream>
#include "../src/Patient/patient.h"

int main()
{
    // Test Case 1: Default constructor
    Patient patient;
    std::cout << "Default Patient Details:\n";
    patient.printDetails();
    std::cout << "Default Patient Type: " << patient.getType() << "\n";
    std::cout << "Nearest Hospital ID: " << patient.getNearestHospitalID() << "\n";

    // Test Case 2: Setting patient details
    Patient::PatientType patientType = Patient::PatientType::SP;
    patient.setFirstName("John");
    patient.setMiddleName("Michael");
    patient.setLastName("Doe");
    patient.setNearestHospitalID(101);
    patient.setPatientType(patientType);

    // Verify the changes
    std::cout << "\nUpdated Patient Details:\n";
    std::cout << "First Name: " << patient.getFirstName() << "\n";
    std::cout << "Middle Name: " << patient.getMiddleName() << "\n";
    std::cout << "Last Name: " << patient.getLastName() << "\n";
    std::cout << "Patient Type: " << patient.getType() << "\n";
    std::cout << "Nearest Hospital ID: " << patient.getNearestHospitalID() << "\n";

    // Test Case 3: Printing details
    std::cout << "\nPrinting Patient Details:\n";
    patient.printDetails();

    return 0;
}
