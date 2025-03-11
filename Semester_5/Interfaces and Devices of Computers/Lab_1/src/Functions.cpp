#include "Functions.h"

void set_backlight(int& backlight, char key)
{
	if (key == 'w')
	{
		--backlight;
		if (backlight < 0)
			backlight = 3;
	}
	if (key == 's')
	{
		++backlight;
		if (backlight > 3)
			backlight = 0;
	}
}

void setColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void menuSleepModeHandler()
{
	if (IsPwrSuspendAllowed())
	{
		system("cls");
		setColor(COLORS::RED);
		SetSuspendState(FALSE, FALSE, FALSE); // 1st FALSE - приостановка системы (спящий режим). 
											  // 2nd FALSE - параметр не имеет никакого эффекта 
											  // 3rd FALSE - события пробуждения включены.
		cout << "Sleep mode was disabled!" << endl;
		Sleep(3000);
		setColor(COLORS::WHITE);
	}
	else
	{
		system("cls");
		setColor(COLORS::RED);
		cout << "Sleep mode in not allowed!" << endl;
		Sleep(3000);
		setColor(COLORS::WHITE);
	}
}

void menuHibernateModeHandler()
{
	if (IsPwrHibernateAllowed())
	{
		system("cls");
		setColor(COLORS::RED);
		SetSuspendState(TRUE, FALSE, FALSE);  // 1st TRUE - режим гибернации, остальное идентично спящему режиму. 
		cout << "Hibernate mode was disabled!" << endl;
		Sleep(3000);
		setColor(COLORS::WHITE);
	}
	else
	{
		system("cls");
		setColor(COLORS::RED);
		cout << "Hibernate mode in not allowed!" << endl;
		Sleep(3000);
		setColor(COLORS::WHITE);
	}
}

void say_goodbye()
{
	system("cls");
	string bye = "GOODBYE!";
	for (auto letter : bye)
	{
		cout << letter;
		Sleep(100);
	}
	Sleep(500);
}

