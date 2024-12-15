#include "ui.h"

UI::UI()
{
    displayInterface();
}

int UI::verifyInput()
{
    int input = 0;

    while (1)
    {
        std::cin >> input;
        if (input == 1 || input == 2) { break; }
    }

    return input;
}

void UI::displayLogoAnimation()
{
    std::cout << "\n\nLOGO\n\n" << std::endl;
}

void UI::displayInterface()
{
    displayLogoAnimation();

    std::cout << "Modes:" << std::endl << std::endl;
    std::cout << "           [1] Silent" << std::endl;
    std::cout << "           [2] Interactive" << std::endl << std::endl;

    mode = verifyInput();

    if (mode == 1)
    {
        Organizer silentMode(1);

        std::cout << std::endl << std::endl;
        std::cout << "Start" << std::endl;
        std::cout << "│" << std::endl;
        std::cout << "├── Loading data from input file.." << std::endl;
        std::cout << "│   └── (file: input_1_1)" << std::endl;

        silentMode.loadInputData();

        std::cout << "│" << std::endl;
        std::cout << "├── Processing simulation..." << std::endl;

        silentMode.simulate();

        std::cout << "│" << std::endl;
        std::cout << "└── Generating output file.." << std::endl;
        std::cout << "    └── (file: output_15_12_2024_09_53)" << std::endl;
        std::cout << std::endl;

        silentMode.generateOutput();
    }
    else if (mode == 2)
    {
        
    }
    else
    {
        std::cout << "batee5" << std::endl;
    }
}