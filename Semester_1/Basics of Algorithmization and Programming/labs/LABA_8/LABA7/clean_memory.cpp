#include "Headers.h"                            //подключение библиотеки

//void clean_memory(char** &str, int &n, char* &new_str, char &choice)  //функция освобождения памяти от указателей на указатели и на строки
//{
//	for (int i = 0; i < n; i++) free(*(str+i)); //чистка памяти от указателей на строки  
//	free(str);                                  //очистка памяти от указателся на массив указателей 
//	if(choice != '1') free(new_str);            //если для new_str была выделена память, то освободить ее 
//}

enum Type { Char, Int, Pointer2x, Pointer };
void clean_memory(enum Type t, ...);            // переменная t принимает значение типа enum Type

void clean_memory_param(char** &str, int &n, char* &new_str, char &choice)
{
	clean_memory(Pointer2x, str, Int, n, Pointer, new_str, Char, choice, '\0');   //обращение к функции освобождения памяти
}

void clean_memory(enum Type t, ...)      // переменная t принимает значение типа enum Type
{
	char choice = 0, *new_str = NULL, **str = NULL;
	int n = 0;
	void *p = &t;                      // все как и в предыдущих функциях
	p = ((int *)p) + 1;
	puts("\n");
	switch (t)
	{
	case Char: while (*(char *)p) p = ((char*)p) + 1; break;
	case Int: while (*(int *)p) p = ((int*)p) + 1; break;
	case Pointer2x: while (*(char*)p) p = ((char***)p) + 1; break;
	case Pointer: while (*(char*)p) p = ((char**)p) + 1; break;
	}
	for (int i = 0; i < n; i++) free(*(str + i)); //чистка памяти от указателей на строки  
	free(str);                                    //очистка памяти от указателся на массив указателей 
	if (choice != '1') free(new_str);             //если для new_str была выделена память, то освободить ее 
}
