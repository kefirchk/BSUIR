#include "File.h"

File::File(const char* newFileName = "")
{
	strcpy_s(_fileName, strlen(newFileName) + 1, newFileName);
}
File::~File()
{}

void File::remove_file()
{
	try {
		if (remove(_fileName))
			throw FileException(1, "Ошибка удаления файла!", "Проверьте наличие или целостность файла");
		Interface<int> iface;
		iface.setColor(GREEN);
		cout << endl << "Файл успешно удален!" << endl << endl;
		iface.setColor(WHITE);
	}
	catch (FileException& err)
	{
		err.what();
	}
}

bool File::exists()
{
	ifstream file;
	try
	{
		file.open(_fileName);
		//if(!file.good())
		//	throw FileException(2, "Ошибка файла!", "Проверьте наличие файла!");
		//if(!file.is_open())
			//throw FileException(2, "Ошибка файла!", "Файл не открыт!");
		if (!file)
			throw FileException(2, "Ошибка файла!", "Проверьте наличие файла!");
		return true;
	}
	catch (FileException& err)
	{
		err.what();
		return false;
	}
}

bool File::create_file()
{
	fstream file(_fileName);
	file.open(_fileName, ios::out | ios::trunc);
	if (file)
	{
		file.close();
		return true;
	}
	return false;
}