#pragma once
#include "Libs.h"
#include "Webcam.h"
#include "Console.h"

// ====================================================================
// ќбъ€вление констант
// --------------------------------------------------------------------
#define VIDEO_FOLDER_NAME "./Video/"  // папка дл€ видео
#define PHOTO_FOLDER_NAME "./Photo/"  // папка дл€ фото
#define VIDEO_FORMAT ".avi"           // расширение видео
#define PHOTO_FORMAT ".jpg"           // расширение фото
#define PHOTO_DELAY 5000              // задержка между фото

// ====================================================================
//  ласс SpyEye
// --------------------------------------------------------------------
class SpyEye
{
public:
	bool isActive = false;                // признак начатой съемки

	SpyEye();                             // конструктор по умолчанию
	~SpyEye();                            // деструктор
	void help();                          // по€снени€ доступных команд
	bool executeCommand(string command);  // выполнить команду
	void printLogo();                     // напечатать логотип программы
	void startSpyVideo();                 // начать запись видео
	void startSpyPhoto();                 // сделать фото
	void mirror();                        // включить режим зеркала
	void aboutCamera();                   // вывести информацию о веб-камере
	Console& getConsole();				  // получить поле console
	string generateFileName(string, string, string); // генераци€ имени файла с индексом

private:
	const string videoName = "video";     // им€ файла дл€ видео
	const string photoName = "photo";     // им€ файла дл€ фото
	set<string> commands = {              // доступные команды
		"mirror",
		"photo",
		"video",
		"info",
		"help",
		"exit"
	};
	VideoCapture camera;                  // объект камеры
	Console console;                      // консоль
};

