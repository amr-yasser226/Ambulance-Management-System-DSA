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

public:
    UI();
    void displayInterface();

    void displayLogoAnimation();
    int verifyInput();
};

#endif // UI_h
