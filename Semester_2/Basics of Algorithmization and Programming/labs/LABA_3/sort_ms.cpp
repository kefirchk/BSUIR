#include "Header.h" //����������� ����������

word* sort_ms(word* ab, int k) //������� ���������� ������� ����� ��������� ���� 
{
	//�������� ���������� ����:
	//"�������"
	
	int temp; //��������� ����������
	char str_temp[n2 + 1] = { }; //��������� ������ ��� �������� ����
	for (int i = 0; i < k; i++) 
	{
		for (int j = i + 1; j < k; j++)
		{
			if (ab[i].repeat < ab[j].repeat) //������������ ������� ��������� �������
			{
				temp = ab[i].repeat;
				ab[i].repeat = ab[j].repeat;
				ab[j].repeat = temp;
				strcpy_s(str_temp, (n2+1)*sizeof(char), ab[i].word);
				strcpy_s(ab[i].word, (n2+1)*sizeof(char), ab[j].word);
				strcpy_s(ab[j].word, (n2+1)*sizeof(char), str_temp);
			}
		}
	}
	return ab; //������� ��������� �� ������ ��������


	//"�������"
	/*int i, j, m, kk;
	for (i = 0; i < k - 1; ++i)
	{
		m = i;                     
		kk = ab[i].repeat;                
		for (j = i + 1; j < k; ++j) 
			if (ab[i].repeat < kk)              
			{
				m = j;               
				kk = ab[i].repeat;
			}
		ab[m].repeat = ab[i].repeat;            
		ab[i].repeat = kk;
	}*/

	//"�������"
	//int i, j, kk;
	//for (i = 1; i < k; ++i)        
	//{
	//	j = i - 1;             
	//	kk = ms[i];               
	//	while (j >= 0 && kk < ms[j])
	//		ms[j-- + 1] = ms[j]; 
	//	ms[j + 1] = kk;           
	//}

	//"������"
	//int i, a, b, c, d;
	//c = 1;
	//b = k - 1;   
	//d = k - 1;   
	//do
	//{
	//	 for (i = d; i >= c; --i)   
	//	 {                          
	//		 if (ms[i - 1] > ms[i])    
	//		 {                       
	//			 a = ms[i - 1];
	//			 ms[i - 1] = ms[i];
	//			 ms[i] = a;
	//			 b = i;             
	//		 }
	//	 }
	//	 c = b + 1;                  
	//	 for (i = c; i <= d; ++i) 
	//	 {                           
	//		 if (ms[i - 1] > ms[i])
	//		 {
	//			 a = ms[i - 1];
	//			 ms[i - 1] = ms[i];
	//			 ms[i] = a;
	//			 b = i;              
	//		 }
	//	 }
	//	 d = b - 1;
	//} while (c <= d);

	//"����"
	/*int i, j, dp, a;
	for (dp = k / 2; dp > 0; dp /= 2)
		for (i = dp; i < k; i++)
			for (j = i - dp; j >= 0 && ms[j] > ms[j + dp]; j -= dp)
			{
				a = ms[j];
				ms[j] = ms[j + dp];
				ms[j + dp] = a;
			}*/
}