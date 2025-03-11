#include "Headers.h"                            //подключение библиотеки

void clean_memory(char** &str, int &n, char* new_str, char &choice)  //функция освобождения памяти от указателей на указатели и на строки
{
	for (int i = 0; i < n; i++) free(*(str+i)); //чистка памяти от указателей на строки  
	free(str);                                  //очистка памяти от указателся на массив указателей 
	if(choice != '1') free(new_str);            //если для new_str была выделена память, то освободить ее 
}