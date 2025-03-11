#pragma once
#include "Libs.h"

// ====================================================================
// Класс Webcam
// --------------------------------------------------------------------
class Webcam
{
public:
	string getData(DWORD property);   // получить данные о веб-камере
	string getDriverName();           // получить имя драйвера веб-камеры
	string getDriverVersion();        // получить версию драйвера веб-камеры
};

