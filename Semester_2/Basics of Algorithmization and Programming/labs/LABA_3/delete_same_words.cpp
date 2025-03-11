#include "Header.h" //подключение библиотеки

word* delete_same_words(word* ab, int &k) //функция удаления в массиве структур одинаковых слов
{
	int lenght = k;             //первоначальное количество слов
	for (int i = 0; i < k; i++)
		if (ab[i].repeat == -1) //пометка, что данное слово нужно удалить
		{
			for (int j = i + 1; j < k; j++) //цикл по сдвигу массива(удаление слова)
			{
				for (int t = 0; t < n2 + 1; t++) ab[j - 1].word[t] = ab[j].word[t];
				ab[j-1].repeat = ab[j].repeat;
			}
			if (ab[i].repeat) i--; //проверка, нужно ли изменять i
			k--;
		}
	if(k != lenght) ab = (word*)realloc(ab, k * sizeof(word)); //перераспредение памяти под указатель на указатели на слова
	if (!ab)         //если не удалось перераспределить память
	{
		puts("Segmentation error!");
		return 0;
	}
	return ab;       //вернуть указатель на указатели
}