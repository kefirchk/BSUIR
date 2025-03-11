#pragma once
#include <iostream>
#include <fstream>
#include "Exception.h"
#include "Interface.h"
using namespace std;

#define PATH "D:\\Projects\\P_in_HLL projects\\3 semester\\LABA_6\\LABA_6\\Files\\"

class File
{
protected:
	char _fileName[80];
public:
	File(const char* newFileName);
	~File();

	void remove_file();
	bool create_file();
	bool exists();
};

