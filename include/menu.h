#ifndef _MENU_H
#define _MENU_H
#include <data.h>

class MenuLCD
{
public:
    void MainMenu();
    void DateTime();
    void DateTimeSet();
    void Lighting();
    void LightingSet();
    void Heating();
    void HeatingSet();
};

#endif