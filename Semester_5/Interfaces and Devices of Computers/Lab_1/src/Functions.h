#pragma once
#include "Libs.h"

void set_backlight(int& backlight, char key);
void setColor(int color);
void say_goodbye();
void move_new_menu();
void mainMenuHandler();
void menuPowerSupplyInfoHandler();
void menuSleepModeHandler();
void menuHibernateModeHandler();
void inputHandler();

