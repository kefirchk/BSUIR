/* Лабораторная работа №3. Наследование.
Вариант 3:
Создать класс "Вычислительная машина".
Требуется реализовать производные классы "Стационарная ВМ" и "Портативная ВМ".
От них соответственно создать производные классы "Моноблок" и "Планшет(смартфон)", "Ноутбук".
Итого, должен получится следующий рез-тат:
                                 _____________________
								|Вычислительная машина|
								     /            \
                     _______________/              \______________
					|Стационарная ВМ|              |Портативная ВМ|
					        |                          /       \
					     ___|____             ________/         \_______
					    |Моноблок|           |Смартфон|         |Ноутбук|
*/                            

#include "Functions.h"
#include <Windows.h>
#define N 1              //размер массива объектов класса ...

int main()
{
	setlocale(LC_ALL, "Rus");
	//=======================================          
	//cout << setw(60) << "РАБОТА С КЛАССОМ <<ВЫЧИСЛИТЕЛЬНАЯ МАШИНА>>\n" << endl;
	//CountingMachine CM[N];
	//CountingMachine newCM;
	//for (int i = 0; i < N; i++)
	//{
	//	cin >> newCM;
	//	cout << endl;
	//	CM[i] = newCM;
	//}
	//outputHatCM();
	//newCM.outputHat();           //шапка таблицы
	//for (int i = 0; i < N; i++)
	//	cout << CM[i];
	//newCM.endOfTable();          //подрисовка таблицы
	//=======================================
	
	//=======================================
	/*cout << setw(70) << "РАБОТА С КЛАССОМ <<СТАЦИОНАРНАЯ ВЫЧИСЛИТЕЛЬНАЯ МАШИНА>>\n" << endl;
	StationaryCM SCM[N];
	StationaryCM newSCM;
	for (int i = 0; i < N; i++)
	{
		cin >> newSCM;
		cout << endl;
		SCM[i] = newSCM;
	}
	newSCM.outputHat();
	for (int i = 0; i < N; i++)
		cout << SCM[i];
	newSCM.endOfTable();*/
	//=======================================

	//=======================================
	//cout << setw(70) << "РАБОТА С КЛАССОМ <<ПОРТАТИВНАЯ ВЫЧИСЛИТЕЛЬНАЯ МАШИНА>>\n" << endl;
	//PortableCM PCM[N];
	//PortableCM newPCM;
	//for (int i = 0; i < N; i++)
	//{
	//	cin >> newPCM;
	//	cout << endl;
	//	PCM[i] = newPCM;
	//}
	//outputHatPCM();
	//newPCM.outputHat();         //шапка таблицы
	//for (int i = 0; i < N; i++)
	//	cout << PCM[i];
	//newPCM.endOfTable();        //подрисовка таблицы
	//=======================================

	//=======================================
	//cout << setw(50) << "РАБОТА С КЛАССОМ <<МОНОБЛОК>>\n" << endl;
	//Monoblock monoB[N];
	//Monoblock newMonoB;
	//for (int i = 0; i < N; i++)
	//{
	//	cin >> newMonoB;
	//	cout << endl;
	//	monoB[i] = newMonoB;
	//}
	//newMonoB.outputHat();        //шапка таблицы
	//for (int i = 0; i < N; i++)
	//	cout << monoB[i];
	//newMonoB.endOfTable();       //подрисовка таблицы
	//========================================
	
	//========================================
	//cout << setw(50) << right << "РАБОТА С КЛАССОМ <<НОУТБУК>>\n" << endl;
	//Notebook notebooks[N];
	//Notebook newNotebook;
	//for (int i = 0; i < N; i++)
	//{
	//	cin >> newNotebook;
	//	cout << endl;
	//	notebooks[i] = newNotebook;
	//}
	//newNotebook.outputHat();        //шапка таблицы
	//for (int i = 0; i < N; i++)
	//	cout << notebooks[i];
	//newNotebook.endOfTable();     	//подрисовка таблицы
	//========================================

	//========================================
	cout << setw(45) << "РАБОТА С КЛАССОМ <<СМАРТФОН>>\n" << endl;
	Smartphone smartphones[N];
	Smartphone newSmartphone;
	for (int i = 0; i < N; i++)
	{
		cin >> newSmartphone;
		cout << endl;
		smartphones[i] = newSmartphone;
	}
	newSmartphone.outputHat();    //шапка таблицы
	for (int i = 0; i < N; i++)
		cout << smartphones[i];	
	newSmartphone.endOfTable();   //подрисовка таблицы

	int num, operation, x;
	char buffer[80];
	cout << "\nВыберите смартфон:" << endl;
	for (int i = 1; i <= N; i++) cout << setw(3) << i;
	cout << endl;
	cin >> num;
	num--;
	while (1)
	{
		cout << "\nВыберите опцию:" << endl;
		cout << "1 - изменить название производителя" << endl;
		cout << "2 - изменить вес" << endl;
		cout << "3 - изменить емкость аккумулятора" << endl;
		cout << "4 - изменить тип экрана" << endl;
		cout << "5 - изменить разрешение камеры" << endl;
		cout << "6 - ничего не изменять" << endl;
		cin >> operation;
		rewind(stdin);
		switch (operation)
		{
		case 1:
			cout << "Введите название производителя" << endl;
			cin.getline(buffer, 80);
			smartphones[num].setBrand(buffer); 
			break;
		case 2:
			cout << "Введите вес" << endl;
			cin >> x;
			smartphones[num].setWeight(x);
			break;
		case 3:
			cout << "Введите емкость аккумулятора" << endl;
			cin >> x;
			smartphones[num].setBatteryCapacity(x);
			break;
		case 4: 
			cout << "Введите тип экрана" << endl;
			cin.getline(buffer, 80);
			smartphones[num].setTouchScreen(buffer);
			break;
		case 5:
			cout << "Введите разрешение камеры" << endl;
			cin >> x;
			smartphones[num].setCameraResolution(x); break;
		case 6: break;
		default: break;
		}
		if (operation == 6) break;
	}
	cout << endl;

	newSmartphone.outputHat();    //шапка таблицы
	for (int i = 0; i < N; i++)
		cout << smartphones[i];
	newSmartphone.endOfTable();   //подрисовка таблицы
	//========================================
	return 0;
}