#include <iostream>
#include "../src/Organizer/organizer.h"

int main() {
    Organizer organizer;

    organizer.loadInputData();
    std::cout << organizer.getValueByMap(12) << std::endl;
    organizer.simulate();
    organizer.generateOutput();

    return 0;
}