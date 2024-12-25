#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>

#include "../Organizer/organizer.h"

class UI
{
private:
    int mode = 0;
    // 0 - unselected
    // 1 - silent
    // 2 - interactive
    // 5 - debugging

public:
    UI();
    void displayInterface();

    void displayLogoAnimation();
    int verifyInput();
    int chooseFile();
};

#endif // UI_h
