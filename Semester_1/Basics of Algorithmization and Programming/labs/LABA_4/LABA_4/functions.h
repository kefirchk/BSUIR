int inputN(int n, char choice);                               //функция ввода порядка матрицы
float** giveMemory(int n, float** matrix);                    //функция выделения памяти
float** inputMatrixElements(int n, float **matrix);           //функция ввода элементов массива
float *algo(int &n, float** matrix, int &flag, float* array); //функция основного алгоритма для решения задачи
void outputOfResult(int n, float **matrix, float* array);     //функция вывода результата
void additional_offer(char choice);                           //функция для выбора, продолжить ли выполнение программы