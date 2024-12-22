#include <iostream>
#include "../src/Organizer/organizer.h"
#include "../src/Hospital/hospital.h"
#include "../src/Patient/patient.h"
#include "../src/Car/car.h"

int main()
{
    Organizer organizer(1);

    organizer.loadInputData();
    organizer.simulate();
    organizer.generateOutput();
    return 0;
}