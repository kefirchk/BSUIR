#include <stdio.h>

int check1(char str[], int i)
{
	static int j, k, m, x;
	switch (str[i])
	{
	case '\0': return 0;
	case '(': if (j >= 0) j++; check1(str, i + 1); break;
	case ')': if(k>=0) j--; check1(str, i + 1); break;
	
	case '[': if (k >= 0) k++; check1(str, i + 1); break;
	case ']': if(j>=0) k--; check1(str, i + 1); break;
	
	case '{': if (m >= 0) m++; check1(str, i + 1); break;
	case '}': m--; check1(str, i + 1); break;
	default:  check1(str, i + 1); break;
	}
	if (j == 0 && k == 0 && m == 0) return j;
	else return -1;
}

int main()
{
	char str[] = "([)]  [()]";
	int result1;
	result1 = check1(str, 0);
	if (result1 == 0) printf("ALL GOOD!");
	else printf("ALL BAD!");
	return 0;
}





//#include <stdio.h>
//#include <stdlib.h>
//#define BRACE_TYPES_COUNT 3
//
//enum Type {
//	SQUARE,
//	CIRCLE,
//	CURLY,
//	IMPOSSIBLE // описывает тип пустой скобки
//};
//
//enum Status {
//	CLOSE,
//	OPEN,
//	SECRET // описывает статус пустой скобки
//};
//
//const char OpenBraces[BRACE_TYPES_COUNT] = { '[', '(', '{' };
//const char CloseBraces[BRACE_TYPES_COUNT] = { ']', ')', '}' };
//
//enum Type GetBraceType(char ch)
//{
//	for (int i = 0; i < BRACE_TYPES_COUNT; i++)
//	{
//		if (ch == OpenBraces[i] || ch == CloseBraces[i])
//			return i;
//	}
//}
//
//enum Status GetBraceStatus(char ch)
//{
//	for (int i = 0; i < BRACE_TYPES_COUNT; i++)
//		if (ch == OpenBraces[i])
//			return 1;
//	return 0;
//}
//
//int* Search(char* str, int i, int *wrong_order)
//{
//	static enum Type last_brace_type = IMPOSSIBLE;
//	static enum Status last_brace_status = SECRET;
//
//	int *sums = (int *)calloc(BRACE_TYPES_COUNT, sizeof(int));
//
//
//	if (str[i] != '\0')
//		sums = Search(str, i + 1, wrong_order);
//	else
//		return sums; // zeros
//
//	enum Type brace_type = GetBraceType(str[i]);
//	enum Status brace_status = GetBraceStatus(str[i]);
//
//	if (brace_status == OPEN)
//		sums[brace_type]++;
//	else
//		sums[brace_type]--;
//
//	 //проверка на ситуации типа ( ] 
//	if (brace_status == OPEN && last_brace_status != brace_status && last_brace_type != brace_type)
//		*wrong_order = 1;
//
//	last_brace_status = brace_status;
//	last_brace_type = brace_type;
//
//	return sums;
//}
//
//int main()
//{
//	char str[] = "()({)}([])[]";
//
//	int wrong_order = 0;
//	int *sums = Search(str, 0, &wrong_order);
//
//	int status = 1;
//	for (int i = 0; i < BRACE_TYPES_COUNT; i++)
//		status &= !sums[i];
//
//	printf(status & !wrong_order ? "good" : "wrong");
//
//	return 0;
//}
