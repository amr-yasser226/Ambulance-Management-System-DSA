#include <iostream>
#include "../src/Organizer/organizer.h"

int main() {
    Organizer organizer;

    organizer.loadInputData();
    organizer.simulate();
    organizer.generateOutput();

    return 0;
}