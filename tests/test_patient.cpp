#include <iostream>
#include "../src/Patient/patient.h" // Include the Patient header

// Function to check if two strings are equal (since we can't use std::string here, we'll use character arrays)
void expectEqual(const std::string &actual, const std::string &expected, const char *testName)
{
    if (actual == expected)
    {
        std::cout << "PASS: " << testName << std::endl;
    }
    else
    {
        std::cout << "FAIL: " << testName << " - Expected " << expected << ", but got " << actual << std::endl;
    }
}

// Function to run a basic test on the Patient class
void testPatientClass()
{
    Patient patient; // Create a Patient object

    // Simulate collecting patient information (you may want to mock or automate input in a real scenario)
    std::cout << "Please enter test data for the Patient class...\n";
    patient.collectAndDisplayPatientInfo(); // This will call the input methods and print details

    // Example test: check if the collected names match expected values
    // (This requires you to manually check the output for now)
    // In real automated testing, you would mock inputs and compare expected outputs
}

// Main function to run all tests
int main()
{
    std::cout << "Running Tests for Patient Class..." << std::endl;
    testPatientClass();
    return 0;
}
