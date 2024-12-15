#include <iostream>
#include "ui.h"

ui::ui()
{
selectMode();
}
int ui::selectMode()
{   bool choose=true;
    int input;
    std::cout<<"Choose [1] interactive Mode [2] Slient Mode :\n";
    std::cin>> input;
    if(input ==1 || input ==2)
    {   
        return input;
    }else{
        while(choose)
        {
            std::cout<<"Please Choose one of the two options above:\n";
            std::cin>>input;
            if(input==1 || input==2)
                choose=false;

        }
        return input;
    }

}
int ui :: getTimestep(int Timestep){
    return Timestep;
}

