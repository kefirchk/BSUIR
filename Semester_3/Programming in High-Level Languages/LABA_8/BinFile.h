#pragma once
#include "File.h"
#include <fstream>
#define BIN ".bin"

template <class T>
class BinFile : public File
{
private:
	fstream _stream;
public:
	BinFile(const char* newFileName = "") : File(newFileName) {}
	~BinFile() {}

	bool openBinFile(int);
	void writeInFile(BinaryTree<T>&);
	void readFromFile(BinaryTree<T>&);

	void writeInFile(multimap<int, T>&);
	void readFromFile(multimap<int, T>&);
};