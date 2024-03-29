#include<dos.h>

#define ATTRIBUTE_1 0x6E   //yellow color
#define ATTRIBUTE_2 0x1E   //blur color
#define HEADER_X 130       //position of any header on x
#define DIGITS_X 142       //position of bits on x

void changeIDT();          //changing of interruption vector table
void initOfControllers();  //initialization
void printToScreen(char*, int, int, unsigned char); //output on display
void byteToString(unsigned char temp, char* str);   //translator byte to string
void update();             //infinite update

//IRQ0-7
void interrupt(*old_int8)(...);   // IRQ 0  - ������
void interrupt(*old_int9)(...);   // IRQ 1  - ����������
void interrupt(*old_int10)(...);  // IRQ 2  - ��������� ������������ ������� �����������
void interrupt(*old_int11)(...);  // IRQ 3  - ���������������� ���� COM 2
void interrupt(*old_int12)(...);  // IRQ 4  - ���������������� ���� COM 1
void interrupt(*old_int13)(...);  // IRQ 5  - ������������ ���� LPT 2
void interrupt(*old_int14)(...);  // IRQ 6  - ���������� ������-��������
void interrupt(*old_int15)(...);  // IRQ 7  - ������������ ���� LPT 1

//IRQ8-15
void interrupt(*old_int70)(...);  // IRQ 8  - ���� ��������� �������
void interrupt(*old_int71)(...);  // IRQ 9  - ���������
void interrupt(*old_int72)(...);  // IRQ 10 - ���������� �������������
void interrupt(*old_int73)(...);  // IRQ 11 - ���������
void interrupt(*old_int74)(...);  // IRQ 12 - ���� PS/2
void interrupt(*old_int75)(...);  // IRQ 13 - �������������� �����������
void interrupt(*old_int76)(...);  // IRQ 14 - ������ ���������� ������� �����
void interrupt(*old_int77)(...);  // IRQ 15 - ������ ���������� ������� �����

// new interrupt handlers
void interrupt new_int8(...) { update(); (*old_int8)(); }
void interrupt new_int9(...) { update(); (*old_int9)(); }
void interrupt new_int10(...) { update(); (*old_int10)(); }
void interrupt new_int11(...) { update(); (*old_int11)(); }
void interrupt new_int12(...) { update(); (*old_int12)(); }
void interrupt new_int13(...) { update(); (*old_int13)(); }
void interrupt new_int14(...) { update(); (*old_int14)(); }
void interrupt new_int15(...) { update(); (*old_int15)(); }
void interrupt new_int70(...) { update(); (*old_int70)(); }
void interrupt new_int71(...) { update(); (*old_int71)(); }
void interrupt new_int72(...) { update(); (*old_int72)(); }
void interrupt new_int73(...) { update(); (*old_int73)(); }
void interrupt new_int74(...) { update(); (*old_int74)(); }
void interrupt new_int75(...) { update(); (*old_int75)(); }
void interrupt new_int76(...) { update(); (*old_int76)(); }
void interrupt new_int77(...) { update(); (*old_int77)(); }

//===========================================================================
//========================BEGINING OF PROGRAM================================
//===========================================================================

void main()
{
	changeIDT();
	initOfControllers();

	unsigned far* fp;  //��������� ���������
	FP_SEG(fp) = _psp; //�������� �������
	FP_OFF(fp) = 0x2c; //�������� �������� �������� ������ � ����������� �����
	_dos_freemem(*fp); //������������ ������ ��� ���
	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1); //��������� ��������� �����������, ���
	                                            //������ �������� � ��� ����������,
	                                            //������ � ����� ������, ������� ������ ���� �������������� 
	                                            //��� ��������� ����� � ����������
}

void changeIDT()
{
	old_int8 = getvect(0x8);      // IRQ0 ���������� �������, ��������� 18,2 ���� � �������.
	old_int9 = getvect(0x9);      // IRQ1 ���������� �� ����������.
	old_int10 = getvect(0xA);     // IRQ2 ������������ ��� �������������� ���������� ����������
	old_int11 = getvect(0xB);     // IRQ3 ���������� ������������ ����� COM2.
	old_int12 = getvect(0xC);     // IRQ4 ���������� ������������ ����� COM1.
	old_int13 = getvect(0xD);     // IRQ5 ���������� �� ����������� �������� ����� ��� XT.
	old_int14 = getvect(0xE);     // IRQ6 ���������� ������������ ������������ ������ ����� ����� ���������� ��������
	old_int15 = getvect(0xF);     // IRQ7 ���������� ��������.

	old_int70 = getvect(0x70);    // IRQ8 ���������� �� ����� ��������� �������.
	old_int71 = getvect(0x71);    // IRQ9 ���������� �� ����������� EGA.
	old_int72 = getvect(0x72);    // IRQ10 ���������������.
	old_int73 = getvect(0x73);    // IRQ11 ���������������.
	old_int74 = getvect(0x74);    // IRQ12 ���������������.
	old_int75 = getvect(0x75);    // IRQ13 ���������� �� ��������������� ������������.
	old_int76 = getvect(0x76);    // IRQ14 ���������� �� ����������� �������� �����.
	old_int77 = getvect(0x77);    // IRQ15 ���������������.

	//��������������� IRQ 0-7 (������� 11)
	setvect(0xB0, new_int8);
	setvect(0xB1, new_int9);
	setvect(0xB2, new_int10);
	setvect(0xB3, new_int11);
	setvect(0xB4, new_int12);
	setvect(0xB5, new_int13);
	setvect(0xB6, new_int14);
	setvect(0xB7, new_int15);

	//��������������� IRQ 8-15 (������� 11)
	setvect(0x08, new_int70);
	setvect(0x09, new_int71);
	setvect(0x0A, new_int72);
	setvect(0x0B, new_int73);
	setvect(0x0C, new_int74);
	setvect(0x0D, new_int75);
	setvect(0x0E, new_int76);
	setvect(0x0F, new_int77);
}

void initOfControllers() 	// �������������
{
	unsigned char register_of_masks;

	_disable(); // Clear Interrupt Flag

	// ������� ����������
	register_of_masks = inp(0x21);  // ���������� ������� �����
	outp(0x20, 0x11);               // ICW1 - ������������� �������� �����������
	outp(0x21, 0xB0);               // ICW2 - ������� ������ ��� �������� (������� 11)
	outp(0x21, 0x04);               // ICW3 - ���� ��� �������� �����������
	outp(0x21, 0x01);               // ICW4 - �� ���������
	outp(0x21, register_of_masks);  // ��������������� ������� �����

	// ������� ����������
	register_of_masks = inp(0xA1);  // ���������� ������� �����
	outp(0xA0, 0x11);               // ICW1 - ������������� �������� �����������
	outp(0xA1, 0x08);               // ICW2 - ������� ������ ��� �������� (������� 11)
	outp(0xA1, 0x02);	            // ICW3 - ���-�� ������������ ������ � ��������
	outp(0xA1, 0x01);	            // ICW4 - �� ���������
	outp(0xa1, register_of_masks);  // ��������������� ������� �����

	_enable(); // STI
}

void byteToString(unsigned char register_int, char* register_str) // ���� � ������ � �������� ����
{
	register_str[8] = 0;
	for (int i = 7; i >= 0; --i)
	{
		register_str[i] = '0' + register_int % 2;
		register_int /= 2;
	}
}

void printToScreen(char* str, int x, int y, unsigned char attribute)
{
	char far* screen = (char far*)0xb8000000;  //�������� ����������
	screen += x + 160 * y;                     //��������
	for (int i = 0; str[i] != 0; ++i, ++screen)
	{
		*screen = str[i];
		screen++;
		*screen = attribute;
	}
}

void update()
{
	unsigned char ISR_master, ISR_slave; // Interrupt Service Register - ������� ������������� ����������
	unsigned char IRR_master, IRR_slave; // Interrupt Request Register - ������� �������� �� ����������
	unsigned char IMR_master, IMR_slave; // Interrupt Mask Register    - ������� �����

	IMR_master = inp(0x21);  //�������� ������� ����� �������� �����������
	IMR_slave = inp(0xA1);   //�������� ������� ����� �������� �����������

	outp(0x20, 0x0A);        //������������ �� ������� �������� �������� �����������
	IRR_master = inp(0x20);  //�������� ������� �������� �������� ����������� 
	outp(0xA0, 0x0A);        //������������ �� ������� �������� �������� �����������
	IRR_slave = inp(0xA0);   //�������� ������� �������� �������� �����������
	
	outp(0x20, 0x0B);        //������������ �� ������� ������������ �������� �����������
	ISR_master = inp(0x20);  //�������� ������� ������������ �������� �����������
	outp(0xA0, 0x0B);        //������������ �� ������� ������������ �������� �����������
	ISR_slave = inp(0xA0);   //�������� ������� ������������ �������� �����������

	char str[9];
	int string_Y = 0;

	printToScreen("====MASTER====", HEADER_X, string_Y++, ATTRIBUTE_1);
	printToScreen("ISR:  ", HEADER_X, string_Y, ATTRIBUTE_1);
	byteToString(ISR_master, str);
	printToScreen(str, DIGITS_X, string_Y++, ATTRIBUTE_1);

	printToScreen("IRR:  ", HEADER_X, string_Y, ATTRIBUTE_1);
	byteToString(IRR_master, str);
	printToScreen(str, DIGITS_X, string_Y++, ATTRIBUTE_1);

	printToScreen("IMR:  ", HEADER_X, string_Y, ATTRIBUTE_1);
	byteToString(IMR_master, str);
	printToScreen(str, DIGITS_X, string_Y++, ATTRIBUTE_1);

	printToScreen("====SLAVE=====", HEADER_X, string_Y++, ATTRIBUTE_2);
	printToScreen("ISR:  ", HEADER_X, string_Y, ATTRIBUTE_2);
	byteToString(ISR_slave, str);
	printToScreen(str, DIGITS_X, string_Y++, ATTRIBUTE_2);

	printToScreen("IRR:  ", HEADER_X, string_Y, ATTRIBUTE_2);
	byteToString(IRR_slave, str);
	printToScreen(str, DIGITS_X, string_Y++, ATTRIBUTE_2);

	printToScreen("IMR:  ", HEADER_X, string_Y, ATTRIBUTE_2);
	byteToString(IMR_slave, str);
	printToScreen(str, DIGITS_X, string_Y, ATTRIBUTE_2);
}