#include "Header.h" //����������� ����������

word* delete_same_words(word* ab, int &k) //������� �������� � ������� �������� ���������� ����
{
	int lenght = k;             //�������������� ���������� ����
	for (int i = 0; i < k; i++)
		if (ab[i].repeat == -1) //�������, ��� ������ ����� ����� �������
		{
			for (int j = i + 1; j < k; j++) //���� �� ������ �������(�������� �����)
			{
				for (int t = 0; t < n2 + 1; t++) ab[j - 1].word[t] = ab[j].word[t];
				ab[j-1].repeat = ab[j].repeat;
			}
			if (ab[i].repeat) i--; //��������, ����� �� �������� i
			k--;
		}
	if(k != lenght) ab = (word*)realloc(ab, k * sizeof(word)); //��������������� ������ ��� ��������� �� ��������� �� �����
	if (!ab)         //���� �� ������� ���������������� ������
	{
		puts("Segmentation error!");
		return 0;
	}
	return ab;       //������� ��������� �� ���������
}