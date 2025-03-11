#include <stdio.h>
#include <conio.h>
#include <locale.h>

int main()     
{
	struct pole
	{unsigned i1 : 1, i2 : 1, i3 : 1, i4 : 1, i5 : 1, i6 : 1, i7 : 1, i8 : 1,
	      i9 : 1, i10 : 1, i11 : 1, i12 : 1, i13 : 1, i14 : 1, i15 : 1, i16 : 1,
	     i17 : 1, i18 : 1, i19 : 1, i20 : 1, i21 : 1, i22 : 1, i23 : 1, i24 : 1,
	     i25 : 1, i26 : 1, i27 : 1, i28 : 1, i29 : 1, i30 : 1, i31 : 1, i32 : 1;
	} *p;     
	setlocale(0, "Rus");

	float k;
	puts("введите число типа FLOAT ");
	scanf_s("%f", &k);
	p = (pole*)&k;
	int *n = (int*)&k;
	printf("\n %X \n",*n);
	printf("Знак  Характеристика                 Мантисса");
	printf("\n %d   %d %d %d %d %d %d %d %d",
		p->i32, p->i31, p->i30, p->i29, p->i28, p->i27, p->i26, p->i25, p->i24);
	printf("   %d %d %d %d %d %d %d",
		p->i23, p->i22, p->i21, p->i20, p->i19, p->i18, p->i17);
	printf(" %d %d %d %d %d %d %d %d",
		p->i16, p->i15, p->i14, p->i13, p->i12, p->i11, p->i10, p->i9);
	printf(" %d %d %d %d %d %d %d %d",
		p->i8, p->i7, p->i6, p->i5, p->i4, p->i3, p->i2, p->i1);
	fflush(stdin);
	getchar();
	return 0;
}
