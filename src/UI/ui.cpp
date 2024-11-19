#include <iostream>
#include "ui.h"

// Constructor
ui::ui()
{
    // Initialization code if necessary
}

// Function to read the interface mode from the user
void ui::readInterfaceMode()
{
    std::cout << "Enter the interface mode (interactive/silent): ";
    char mode[15];
    std::cin >> mode;
    // You may need to store or process the mode input
}

// Function to read the input and output file names from the user
void ui::readFileNames(char *inputFileName, char *outputFileName)
{
    std::cout << "Enter input file name: ";
    std::cin >> inputFileName;
    std::cout << "Enter output file name: ";
    std::cin >> outputFileName;
}

// Function to display the system status at the end of each timestep
void ui::displaySystemStatus(LinkedQueue<void *> &npQueue,
                             PriorityQueue<void *> &spQueue,
                             PriorityQueue<void *> &epQueue,
                             void **hospitals, int numHospitals)
{
    std::cout << "\n--- System Status ---\n";
    // Loop over hospitals to display their data
    for (int i = 0; i < numHospitals; ++i)
    {
        std::cout << "============== HOSPITAL #" << (i + 1) << " data ==============\n";
        // Display hospital-specific queues and cars here
    }

    // Display Non-Priority (NP) Queue
    std::cout << "Non-Priority Queue:\n";
    npQueue.print(); // This assumes the LinkedQueue class has a print() method

    // Display Special Priority (SP) Queue
    std::cout << "Special Priority Queue:\n";
    spQueue.print(); // This assumes the PriorityQueue class has a print() method

    // Display Emergency Priority (EP) Queue
    std::cout << "Emergency Priority Queue:\n";
    epQueue.print(); // This assumes the PriorityQueue class has a print() method
}

// Function to display details of a specific request
void ui::printRequestDetails(const char *type, int qt, int pid, int hid, int dst, int svr)
{
    std::cout << "Request Type: " << type << ", Time: " << qt
              << ", Patient ID: " << pid << ", Hospital ID: " << hid
              << ", Distance: " << dst;
    if (svr != -1)
    {
        std::cout << ", Severity: " << svr;
    }
    std::cout << "\n";
}

// Function to display details of a cancellation
void ui::displayCancellation(int ct, int pid)
{
    std::cout << "Cancellation at Time: " << ct << ", Patient ID: " << pid << "\n";
}

// Function to run the simulation in interactive mode
void ui::interactiveMode(LinkedQueue<void *> &npQueue, PriorityQueue<void *> &spQueue,
                         PriorityQueue<void *> &epQueue, void **hospitals, int numHospitals)
{
    std::cout << "Interactive Mode: Press Enter to display the next timestep...\n";
    // Simulation loop in interactive mode
    while (true)
    {
        displaySystemStatus(npQueue, spQueue, epQueue, hospitals, numHospitals);
        std::cin.get(); // Wait for user input to proceed to the next timestep
        // Logic to continue or break the loop goes here
    }
}

// Function to run the simulation in silent mode
void ui::silentMode()
{
    std::cout << "Silent Mode: Simulation Starts...\n";
    std::cout << "Simulation ends, Output file created.\n";
}
