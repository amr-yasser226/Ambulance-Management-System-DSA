#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "../Hospital/hospital.h"
#include "../Data Structures/Node.h"
#include "../Data Structures/Request.h"
#include "../Data Structures/PriorityQueue.h"
#include "../Patient/patient.h"

#include <iostream>
#include <fstream>
#include <string>

class Organizer
{
private:
    Node<Hospital>* hospitals;
    priQueue<Request>* requests;
    int hospitalCount = 0;
    int specialCarSpeed = 0, normalCarSpeed = 0;
    int currentTime = 1;


public:
    Organizer();
    ~Organizer();
    
    int getValueByMap(int index);               // Example: getValueByMap(12) will return value at row index 0 at column index 1
    //                                                      getValueByMap(11) or getValueByMap(33) will return 0 always
    //                                                      if return is -1, then index not found
    //                                                      if return is -2, then error opening input file
    void addHospital(Hospital* hospitalInstance);

    void loadInputData();
    void simulate();
    void generateOutput();
};

#endif // ORGANIZER_H
