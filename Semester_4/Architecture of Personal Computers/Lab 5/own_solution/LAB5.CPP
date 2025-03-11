#include <io.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int exit_flag = 0;

void interrupt(*old_int_09h)(...);
void interrupt new_int_09h(...);

void turn_key_indicator(int mask);
void flashing_mode();
void input_mode();

void main() {
	char option = '1';
	while (option != '0')
	{
                rewind(stdin);
		printf("Choose an option:\n1. Flashing mode;\n2. Input mode;\n0. Exit.\n");
		scanf("%c", &option);
		switch (option)
		{
		case '1': flashing_mode(); break;
		case '2': input_mode(); break;
		case '0': break;
		default: puts("\nError!");
		}
	}
}

void turn_key_indicator(int mask) {

	if (mask != 0xED)            //at first we must send 0xED in the port
		turn_key_indicator(0xED);
	while((inp(0x64) & 2) != 0); //check for freedom of keyboard controller input register (check buffer)
	int i = 0; 
	do {
		i++;
		outp(0x60, mask);
	} while (inp(0x60) == 0xFE && i < 3); //3 attemps of sending or while not ERROR
	if (i == 3) {
		printf("\nERROR: 0xFE\n");
		exit_flag = 1;                    //exit from input mode
	}
}

void input_mode()
{
	disable();
	old_int_09h = getvect(0x09); //safe old vector
	setvect(0x09, new_int_09h);  //set new vector
	enable();
	printf("\n(ESC) - Exit\nPress any key...\n");
	while (!exit_flag);          //input of keys
	disable();
	setvect(0x09, old_int_09h);  //set old vector
	enable();
	exit_flag = 0;
}

void flashing_mode()
{
	puts("Look at the CAPSLOCK and NUMLOCK");
	for (int i = 3000; i >= 0; i -= 1000)
	{
		turn_key_indicator(4); //turn on indicator CapsLock
		delay(i);
		turn_key_indicator(0); //turn off all indicators
		turn_key_indicator(2); //turn on indicator NumLock
		delay(i);
		turn_key_indicator(0); //turn off all indicators
	}
	delay(1000);
	turn_key_indicator(6);     //turn on CapsLock and NumLock
	delay(3000);
	turn_key_indicator(0);
}

void interrupt new_int_09h(...)
{
	char buf[5] = "";
	unsigned char c = inp(0x60);   //take scan code
	if (c == 0x01)
		exit_flag = 1;             //if ESC set exit
	if (c != 0xFA && !exit_flag) {    //else show scan code
		itoa(c, buf, 16);
		for (int i = 0; i < 4; ++i)
		{
			if (buf[i] >= 'a' && buf[i] <= 'z')
				buf[i] += 'A' - 'a';
		}
		printf("%sh", buf);
		if ((buf[0] == 'E' && buf[1] == '0')
			|| (buf[2] == 'E' && buf[3] == '0'))
			printf(" ");
		else
			printf("\n");
	}
	(*old_int_09h)();  //return old interrupt 09h
}