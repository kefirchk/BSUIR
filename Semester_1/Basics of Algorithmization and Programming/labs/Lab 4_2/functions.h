void inputN(int n, char choice);                          //функция ввода порядка матрицы
int** giveMemory(int n);                                  //функция выделения памяти
void inputMatrixElements(int n, int **matrix);            //функция ввода элементов массива
void algo(int n, int **matrix);                           //функция основного алгоритма для решения задачи
void outputOfResult(float sumDio, float sumDown, float sumUp);  //функция вывода результата