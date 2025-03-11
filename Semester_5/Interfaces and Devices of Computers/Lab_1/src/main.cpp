#include "Functions.h"
#include "PowerSupply.h"


int main() {
	mainMenuHandler();
	setColor(COLORS::WHITE);
	say_goodbye();
	return 0;
}

void mainMenuHandler()
{
	do {
		system("cls");
		setColor(COLORS::WHITE);
		cout << setw(26) << right << "<< MAIN MENU >>" << endl;
		cout             << " ==================================" << endl;
		backlight == 0 ? setColor(COLORS::GREEN) : setColor(COLORS::WHITE);
		cout <<             "| ->> Power supply information <<- |" << endl;
		backlight == 1 ? setColor(COLORS::GREEN) : setColor(COLORS::WHITE);
		cout <<             "| ->>        Sleep mode        <<- |" << endl;
		backlight == 2 ? setColor(COLORS::GREEN) : setColor(COLORS::WHITE);
		cout <<             "| ->>      Hibernate mode      <<- |" << endl;
		backlight == 3 ? setColor(COLORS::GREEN) : setColor(COLORS::WHITE);
		cout <<             "| ->>           Exit           <<- |" << endl;
		setColor(COLORS::WHITE);
		cout             << " ==================================" << endl;
		Sleep(300);
		key = _getch();
		switch (key)
		{
			case '\r': key = ' '; move_new_menu(); break;
			case 'w': set_backlight(backlight, key); break;
			case 's': set_backlight(backlight, key); break;
		}
	} while (key != EXIT);
}

void menuPowerSupplyInfoHandler()
{
	thread menuThread(inputHandler);
	PowerSupply powerSupply;
	do {
		system("cls");
		powerSupply.update();
		setColor(COLORS::YELLOW);
		cout << setw(40) << right << "<< Power supply information >>" << endl;
		setColor(COLORS::WHITE);
		cout <<             " ==============================================" << endl;
		cout << powerSupply;
		cout <<             " ==============================================" << endl;
		setColor(COLORS::YELLOW);
		cout << setw(10) << "| ->>                 Back                 <<- |" << endl;
		setColor(COLORS::WHITE);
		cout <<             " ==============================================" << endl;
		Sleep(300);
	} while (key != '\r');
	menuThread.join();
}

void inputHandler()
{
	do {
		key = _getch();
	} while (key != '\r');
}

void move_new_menu()
{
	switch (backlight) // сейчас backlight указывает на то меню, куда мы перейдем
	{
	case 0: menuPowerSupplyInfoHandler(); break;
	case 1: menuSleepModeHandler(); break;
	case 2: menuHibernateModeHandler(); break;
	case 3: key = EXIT; break;
	}
}