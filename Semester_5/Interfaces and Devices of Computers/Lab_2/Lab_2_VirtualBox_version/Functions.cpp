#include "Functions.h"

int table_width = 111;

void print_hat()
{
	cout << " ";
	for (int i = 0; i < table_width; ++i)
		cout << "_";
	cout << endl << 
		setw(5) << left << "|Index" << 
		setw(86) << left << "|Device name" << 
		setw(9) << left << "|Device ID" <<
		setw(9) << left << "|Vendor ID" << "|" << endl;
	cout << "|";
	for (int i = 0; i < table_width; ++i)
		cout << "=";
	cout << "|" << endl;
}

void print_end()
{
	cout << " ";
	for (int i = 0; i < table_width; ++i)
		cout << "=";
	cout << endl;
}
