#include "Functions.h"

// Print hat of the table
void printHat()
{
	cout << " " << setw(TABLE_WIDTH) << setfill('_') << "";
	cout << endl << setfill(' ') <<
		setw(30) << left << "| Device parameter" <<
		setw(42) << left << "| Description" << "|" << endl << "|";
	cout << setw(TABLE_WIDTH) << setfill('=') << "" << "|" << endl;
}

// Print end of the table
void printEnd()
{
	cout << "|" << endl << " " << setw(TABLE_WIDTH) << setfill('=') << "" << endl;
} 