#pragma once
#include "File.h"
#include <fstream>
#define TXT ".txt"

template<class T>
class TxtFile : public File
{
private:
	ofstream _fout;
	ifstream _fin;
public:
	TxtFile(const char* newFileName = "") : File(newFileName) {}
	~TxtFile() {}

	bool openForWrite(int option);
	bool openForRead();
	
	void readFromFile(BinaryTree<T>& tree);
	void writeInFile(BinaryTree<T>& tree);
};