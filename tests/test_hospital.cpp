#include <iostream>
#include "../src/Hospital/hospital.h"
#include "../src/Patient/patient.h"
#include "../src/Car/car.h"

int main() {
    Hospital hospital(1);
    hospital.addCars(Car::CarType::SC, 5);
    std::cout << "Special Cars: " << hospital.getNumberOfCars(0) << std::endl;
    return 0;
}
