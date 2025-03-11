//#include <stdio.h>
//#include <conio.h>
//#include <math.h>
//#include <windows.h>
//#include <locale.h>
//// функция получения записи числа из десятичной системы счисления
//// в системе счисления с основанием S (от 2 до 16)
//
//int main()
//{
//	char ms[20], znak = '+';
//	int s, k1 = 10, k2 = 11, t, num1, i;
//	double num;
//	setlocale(LC_ALL, "Russian");         // русификация вывода информации на экран          
//	printf("\nВведите исходное число : ");
//	scanf_s("%lf", &num);
//	num < 0 ? znak = '-', num *= -1 : num;  // выделение знака числа
//	printf("\nВведите основание новой с/с : ");
//	scanf_s("%d", &s);
//	printf("\nВведите точность для дробной части числа с/с : ");
//	scanf_s("%d", &t);
//	system("CLS");                        // очистка экрана
//	num1 = num;                           // выделение целой части числа
//	num -= num1;                          // выделение дробной части числа
//			  //перевод целой части числа
//	while (num1 >= s)            // цикл пока целая часть от деления не меньше S           
//	{
//		i = num1 % s;            // получаем остаток от деления на основание
//		num1 /= s;               // получаем целую часть от деления
//		ms[k1--] = i > 9 ? i - 10 + 'a' : i + '0';     // запоминаем полученную (очередную) цифру
//	}
//	ms[k1--] = num1 > 9 ? num1 - 10 + 'a' : num1 + '0';// запоминаем послелнюю цифру целой части
//	ms[k1] = znak;               // добавляем знак числа
//	ms[k2++] = '.';              // добавляем точку между целой и дробной частями
//			  //перевод дробной части числа
//	while (num != 0 && k2 - 11 <= t)  // цикл пока дробная часть не равна 0 или не достигнута точность
//	{                                 // получаем произведение и выделяем целую и дробную части
//		num = (num *= s, i = num, num -= i);
//		ms[k2++] = i > 9 ? i - 10 + 'a' : i + '0';     // запоминаем полученную (очередную) цифру
//	}
//	printf("\n");
//	for (i = k1; i < k2; i++) printf("%c", ms[i]);
//
//	printf("\n");
//	return 0;
//}


//#include <stdio.h>
//
//int check1(char str[], int i)
//{
//	static int j, k, m;
//	switch (str[i])
//	{
//	case '\0': return 0;
//	case '(': if (j >= 0) j++; check1(str, i + 1); break;
//	case ')': j--; check1(str, i + 1); break;
//	case '[': if (k >= 0) k++; check1(str, i + 1); break;
//	case ']': k--; check1(str, i + 1); break;
//	case '{': if (m >= 0) m++; check1(str, i + 1); break;
//	case '}': m--; check1(str, i + 1); break;
//	default:  check1(str, i + 1); break;
//	}
//	if (j == 0 && k == 0 && m == 0) return j;
//	else return -1;
//}

//int check(char str[], int i) 
//{
//	static int j;
//	switch (str[i]) 
//	{
//	case '\0': return 0;
//	case '(': if (j >= 0) j += 1; check(str, i + 1); return j;
//	case ')': j -= 1; check(str, i + 1); return j;
//	default:  check(str, i + 1); return j;
//	}
//}

//int check1(char str[], int i) 
//{
//	static int j;
//	switch (str[i])
//	{
//	case '\0': return 0;
//	case '[': if (j >= 0) j++; check1(str, i + 1); return j;
//	case ']': j--; check1(str, i + 1); return j;
//	default:  check1(str, i + 1); return j;
//	}
//}

//int check2(char str[], int i) 
//{
//	static int j;
//	switch (str[i])
//	{
//	case '\0': return 0;
//	case '{': if (j >= 0) j++; check2(str, i + 1); return j;
//	case '}': j--; check2(str, i + 1); return j;
//	default:  check2(str, i + 1);
//	}
//}

//int main()
//{
//	char str[] = "[({])}";
//	int result=0, result1, result2=0;
//	//result = check(str, 0);
//	result1 = check1(str, 0);
//	//result2 = check2(str, 0);
//	if (result == 0 && result1 == 0 && result2 == 0) printf("ALL GOOD!");
//	else printf("ALL BAD!");
//	return 0;
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
// //Рекурсивная функция нахождения НОД двух чисел
//int nod(int a,int b);
//int main()
//{  setlocale(LC_ALL,"Russian" );
//   int i,a,b;
//   do
//   { fflush(stdin);
//     printf("");
//     i=scanf_s("%d%d",&a,&b);
//   }while(i<2);
//   printf("\nНОД чисел %d и %d равен %d\n",a,b,nod(a,b));
//}
//
//int nod(int a,int b)  
//{  int c;
//   if (b>a) c=nod(b,a);
//   else if (b<=0) c=a;
//   else c=nod(b,a%b);
//   return c;
//}


//#include <stdio.h>
//#include <locale.h>
//#include <stdlib.h>
//// Рекурсивная функция сортировки методом Хоара
//void hoor(int *, int, int);
//void swap(int *, int, int);
//void FOR(int *, int, int, int, int &);
//
//// рекурсивная функция ввода информации в массив 
//int Vvod(int *MS, int k)
//{
//	static int i = 0;
//	int j;
//	if (!MS) return 1;                 // проверка не нулевой ли указатель на массив 
//	if (i >= k) return 0;              // массив введен полностью
//									   // рекурсия окончена
//	printf("MS[ %d ] = ", i);
//	fflush(stdin); //rewind(stdin);    // чистка входного буфера
//	if (scanf_s("%d", MS + i)) i++;      // проверка введено ли число
//	Vvod(MS, k);                        // рекурсия для ввода очередного элемента
//	i--;
//	return 0;
//}
//
//// рекурсивная функция вывода на экран информации из массива
//void Print(int MS[], int k)       //  здесь MS[] и *MS  - эквивалентны  
//{
//	static int i;
//	if (!MS) return;              // проверка не нулевой ли указатель на массив
//	if (i >= k) return;
//	printf("%4d", *(MS + i++));   // рекурсивный поэлементный вывод массива на экран 
//	Print(MS, k);
//	i--;
//	if (!i) printf("\n");
//	//i = 0;
//	return;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int *ms, i, n;
//	do
//	{
//		fflush(stdin);
//		puts("\nВводите кол-во чисел");
//		i = scanf_s("%d", &n);
//	} while (i<1 || n<=0);
//	ms = (int*)malloc(n*sizeof(int));
//	puts("\nВводите элементы массива ");
//	Vvod(ms,n);
//	system("CLS");
//	printf("\nИсходный массив        :");
//	Print(ms,n);
//	hoor(ms, 0, n - 1);
//	printf("\n\nПреобразованный массив :");
//	Print(ms, n);
//}
//
//// рекурсивная функция сортировки методом Хоара
//void hoor(int *a, int l, int r)
//{
//	int i, las;
//	if (l >= r)  return;
//	swap(a, l, (l + r) / 2);  // делящий эл-т переносится в a[l] (a[l]<->a[(l+r)/2])
//	las = l;                  // позиция посл-го эл-та большего чем делящий
//	//for (i = l + 1; i <= r; i++) //деление [l,r] на [l,las-1] и [las+1,r]
//	//if (a[i]<a[l])         // ЦИКЛ УБРАТЬ !!!!!!!!!!!!!!!!!!!!
//	//	swap(a, ++las, i);
//	FOR(a, l, r, l+1, las);   // замена цикла for рекурсивной функцией FOR
//	swap(a, l, las);
//	hoor(a, l, las - 1);      // сортировка для [l,las-1]
//	hoor(a, las + 1, r);      // сортировка для [las+1,r]
//}
//  
//// функция ( не рекурсивная) замены i и j эл-тов в массиве a
//void swap(int *a, int i, int j)
//{
//	int tmp;           
//	tmp = a[i];
//	a[i] = a[j];
//	a[j] = tmp;
//}
//
//// рекурсивная функция заменяющая традиционный цикл for
//void FOR(int *a, int l, int r, int i, int &las)
//{ 
//	if (i > r) return;
//	if (a[i]<a[l])
//		swap(a, ++las, i);
//	FOR(a,l,r,++i,las);
//}



//------------------------------   пример 3  ------------------------------------------
// В командной строке вводится несколько строк.
// В рекурсивной функции для каждой строки выполнить
// реверсивный переворот последнего слова
// например:     asdf "abc d efg 12345 qwert" 
//#include <stdio.h>
//#include <locale.h>
//
//void fun(char *, int);
//int main(int argc,char *argv[])
//{ setlocale(LC_ALL, "Russian");
//  int i;
//  for(i=1;i<argc;i++)    // обработка очередной строки
//  {                      
//	printf("\n исходная строка:        %s", argv[i]);
//	fun(argv[i],0);        // вызов функции передача в функцию строки argv[i]
//	printf("\n преобразованная строка: %s", argv[i]);
//  }
//  puts("\n\n");
//  return 0;
//}
//
//void fun(char *s,int i)
//{
//  static int j;
//  char c;                     // локальная переменная для сохранения очередного символа строки 
//  if (*(s+i)==' ') j=i+1;     // запоминаем позицию ' ' перед словом
//  if (*(s+i))                 // если не достигнут конец строки
//  { c=*(s+i++);               // то чтение очередного символа из строки
//    fun(s,i);                 // рекурсивный вызов fun
//  }
//  else return;                // строка окончена
//    printf("\n i= %d  j= %d",i,j);
//  if (*(s+j))  *(s+j++)=c;    // реверс слова (запись в строку символов сохраненных при рекурсии)
//  if (i==1) j = 0;            // сброс в 0 индекса (для очередного вызова fun) для новой строки
//}



//===================================================================

//// рекурсивные функции перевода числа из десятичной с/с в новую (2 ... 16)
//#include <stdio.h>
//#include <locale.h>
//
//void fc(int);           // прототип рекурсивной ф-ции перевода целой части числа
//void fd(double, int);   // прототип рекурсивной ф-ции перевода дробной части числа
//
//int ss;                             // основание новой с/с
//char znak = '+';
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int t;                       // точность дробной части
//	double num;                  // исходное число (правильная дробь)
//	printf("\nВведите исходное число : ");
//	scanf_s("%lf", &num);
//	num < 0 ? znak = '-', num *= -1 : num;  // выделение знака числа
//	printf("\nВведите основание новой с/с");
//	scanf_s("%d", &ss);
//	printf("\nВведите точность для дробной части числа с/с");
//	scanf_s("%d", &t);
//	printf("\nЧисло в с/с (%d) = ", ss);
//	fc((int)num);                 // передача в функцию целой части числа
//	putchar('.');
//	fd(num - (int)num, t);           // передача в функцию дробной части числа          
//	puts("\n");
//	return 0;
//}
//
//void fc(int num1)    // рекурсивная функция перевода (вывода на экран) в новую с/с
//{                    // целой части исходного десятичного числа 
//	int i;
//	if (num1 >= ss)
//	{
//		i = num1 % ss;      // получаем остаток от деления на основание
//		num1 /= ss;       // получаем целую часть от деления
//		fc(num1);       // рекурсивный вызов функции fc
//		printf("%c", i > 9 ? i - 10 + 'a' : i + '0');
//	}
//	else printf("%c %c", znak, num1 > 9 ? num1 - 10 + 'A' : num1 + '0');
//}
//
//void fd(double num, int t)   // рекурсивная функция перевода (вывода на экран) в 
//{                            // новую с/с дробной части исходного десятичного числа 
//	static short int n;
//	int i;
//	if (num != 0 && n++ < t)
//	{
//		i = num *= ss;             // получаем произведение и выделяем целую частьk
//		printf("%c", i > 9 ? i - 10 + 'a' : i + '0');
//		fd(num - (int)num, t);    // рекурсивный вызов fd
//	}
//	// else printf("%c",num>9?(int)num-10+'A':(int)num+'0');
//}
//
////=====================================================================


//================================================================
////рекурсивная функция удаления последнего слова
//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//
//int recurs_last_word(char* s, int begin, int end)
//{
//	if (begin < end) 
//	{
//		char temp = s[begin];
//		s[begin] = s[end];
//		s[end] = temp;
//		recurs_last_word(s, begin + 1, end - 1);
//	}
//	return 0;
//}
//
//int main()
//{
//	char s[] = "abcd efg 12345";
//	int j = 0;
//	while (s[j] != '\0')j++;
//	int end = --j;
//	while (s[j] != ' ')j--;
//	int begin = ++j;
//	recurs_last_word(s, begin, end);
//	for (int i = 0; s[i] != '\0'; i++)
//	{
//		printf("%c", s[i]);
//	}
//	return 0;
//}
//==================================================================================

//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//#include <locale.h>
//
//int delete_word(char* s, int j, int lenght)
//{
//	if (s[j]!='\0') 
//	{
//		s[j] = s[j + lenght];
//		delete_word(s, j + 1, lenght);
//	}
//	return 0;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Rus");
//	char s[] = "abcd efg 12345";
//	int n=0, i;
//	printf("Какое слово по счёту вы хотите удалить?\n");
//	scanf_s("%d", &n);
//	int j = 0;
//	int t = 1;
//	while (t != n && s[j]!='\0')
//	{
//		if (s[j] == ' ') t++;
//		j++;
//	}
//	if (t != n) { puts("ERROR!"); return 1;}
//	int begin = j;
//	while (s[j] != ' ' && s[j] != '\0') j++;
//	int end = j;
//	int lenght = end - begin;
//	delete_word(s, begin, lenght);
//	for (int i = 0; s[i] != '\0'; i++)
//	{
//		printf("%c", s[i]);
//	}
//	return 0;
//}


// Рекурсивное вычисление чисел принадлежащих посл-сти Фибоначчи
// сформировать последовательность из 15 чисел:  1 1 2 3 5 8 13 .....
//int fibon(int);      // прототип рекурсивной функции
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int n, i;
//	printf("\nЧисла Фибоначчи =  ");
//	for (n = 0; n<15; n++) 
//	  printf("%4d",fibon(n));
//	puts("\n\n");
//	return 0;
//}
//
//int fibon(int n)  // рекурсивная функция 
//{
//	return ((n == 0 || n == 1)) ? 1 : fibon(n - 1) + fibon(n - 2);
//}



////------------------------------  float  ---------------------------------------------
//#include <stdio.h>
//#include <locale.h>
//
//int main()     
//{
//	struct pole
//	{unsigned i1 : 1, i2 : 1, i3 : 1, i4 : 1, i5 : 1, i6 : 1, i7 : 1, i8 : 1,
//	      i9 : 1, i10 : 1, i11 : 1, i12 : 1, i13 : 1, i14 : 1, i15 : 1, i16 : 1,
//	     i17 : 1, i18 : 1, i19 : 1, i20 : 1, i21 : 1, i22 : 1, i23 : 1, i24 : 1,
//	     i25 : 1, i26 : 1, i27 : 1, i28 : 1, i29 : 1, i30 : 1, i31 : 1, i32 : 1;
//	} *p;     
//	setlocale(0, "Rus");
//
//	float k;
//	puts("введите число типа FLOAT ");
//	scanf_s("%f", &k);
//	p = (pole*)&k;
//	int *n = (int*)&k;
//	printf("\n %X \n",*n);
//	printf("Знак  Характеристика                 Мантисса");
//	printf("\n %d   %d %d %d %d %d %d %d %d",
//		p->i32, p->i31, p->i30, p->i29, p->i28, p->i27, p->i26, p->i25, p->i24);
//	printf("   %d %d %d %d %d %d %d",
//		p->i23, p->i22, p->i21, p->i20, p->i19, p->i18, p->i17);
//	printf(" %d %d %d %d %d %d %d %d",
//		p->i16, p->i15, p->i14, p->i13, p->i12, p->i11, p->i10, p->i9);
//	printf(" %d %d %d %d %d %d %d %d",
//		p->i8, p->i7, p->i6, p->i5, p->i4, p->i3, p->i2, p->i1);
//	fflush(stdin);
//	getchar();
//	return 0;
//}
