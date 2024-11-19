#ifndef UI_H
#define UI_H

#include "../Data Structures/LinkedQueue.h"   // Correct way to include the header                    // Include your LinkedQueue header file
#include "../Data Structures/PriorityQueue.h" // Include your PriorityQueue header file

class ui
{
public:
    // Constructor
    ui();

    // Function to read the interface mode from the user
    void readInterfaceMode();

    // Function to read the input and output file names from the user
    void readFileNames(char *inputFileName, char *outputFileName);

    // Function to display the system status at the end of each timestep
    void displaySystemStatus(LinkedQueue<void *> &npQueue,
                             PriorityQueue<void *> &spQueue,
                             PriorityQueue<void *> &epQueue,
                             void **hospitals, int numHospitals);

    // Function to display details of a specific request
    void printRequestDetails(const char *type, int qt, int pid, int hid, int dst, int svr = -1);

    // Function to display details of a cancellation
    void displayCancellation(int ct, int pid);

    // Function to run the simulation in interactive mode
    void interactiveMode(LinkedQueue<void *> &npQueue, PriorityQueue<void *> &spQueue,
                         PriorityQueue<void *> &epQueue, void **hospitals, int numHospitals);

    // Function to run the simulation in silent mode
    void silentMode();
};

#endif // UI_H
