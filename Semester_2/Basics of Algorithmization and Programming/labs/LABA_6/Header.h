#include <locale.h>    //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define len 15
//����� ����� ��� ���� � �������

struct people //��������� "����", ������������ � ��������������� ������
{
	char name[len+1];         //��� ��������
	char surname[len+1];      //������� ��������
	char faculty[len+1];      //���������
	int group;                //������
	people* next_person;      //��������� �� ���������� ��������
	people* previous_person;  //��������� �� ����������� ��������
};

struct rooms  //��������� "�������", ������������ � ���������������� �������
{
	int numberOfRoom;         //����� �������
	int countOfPeople;        //���������� �������
	people* human;            //��������� �� ��������������� ������ ����������� �����
	rooms* next_room;         //��������� �� ��������� �������
};

struct floor  //��������� "����", ������������ � ��������������� �������
{
	int numberOfFloor;        //����� �����
	int allPlaces;            //��� ����� �� �����
	int freePlaces;           //��������� ����� �� �����
	rooms* room;              //��������� �� ���������������� ������� ������          
	floor* next_floor;        //��������� �� ��������� ����
	floor* previous_floor;    //���������  �� ���������� ����
};

void menu_add(floor*&, floor*&, int* ms); //������� ������� ��������� �������� � ���������
int fun_add(floor*&, floor*&, people*, int *ms, int floorNumber, int roomNumber); //������� ��������� �������� � ���������
people* menu_del(floor*&, floor*&);       //������� ������� ��������� �������� �� ���������
int fun_del(floor*&, floor*&, people*, int floorNumber, int roomNumber); //������� ��������� �������� �� ���������
int search_person(floor*&, floor*&, rooms*&, people* person, int , int); //������� ������ �������� � ���������
void add_from_queue(floor*&, floor*&, people**, people**, int* ms); //������� ��������� �������� �� ������� �� ���������
void set(people**, people**);             //������� ������ �������� � ������� �� ���������
void move(floor*&, floor*&, int* ms);     //������� ����������� �������� �� ����� ������� � ������
int check_free_places(floor*, int*);      //������� �������� ��������� ���� � ���������
void show(floor* tail);                   //������� ��������� ���������� � ���������� ����� � ������ �����
void deleted_plus_queue(people** headHuman, people** tailHuman, people* person); //������� ���������� �������� � ������ ���������� �����
void output_deleted(people* tailDeleted); //������� ������ ������ ���������� �����

void copy_info(people* &newHuman, people* &person); //������� ����������� ���������� � �������� �� ����� ��������� � ������
floor* memory1();        //������� ��������� ������ ��� ����
rooms* memory2();        //������� ��������� ������ ��� �������
people* memory3();       //������� ��������� ������ ��� ��������
void input_person_info(people* &person); //������� ����� ���������� � ��������

int* input_basic_info(); //������� ����� �������� ���������� (���������� ������, ���������� ������ �� �����, ����������� ������)
char* input_str();       //������� ����� ������
int input_int();         //������� ����� ������ �����
int offer();             //������� ������ ���������� ��� ��������� ���������� ���������  
void freeAll(floor* &tailFloor, people* &tailHuman, people* &tailDeleted); //������� ��������� ����������� ������ �� �������� � ������
void instructions();     //������� ������ ���������� ������ ���������
