#include "functions.h"

int main(int argc, char* argv[]) {
    
    struct record_s records[AMOUNT_OF_RECORDS];  // записи в файл
    FILE* file;                                  // файловый дескриптор

    // Проверка количества аргументов командной строки
    if(argc != 2) {
        fprintf(stderr, "Error: command line arguments are incorrect\n");
        printf("Format: ./generator [имя_файла]\n");
        return -1;
    }
    
    // Установка генератора случайных чисел
    srand(time(NULL));

    // Генерация записей
    for(int i = 0; i < AMOUNT_OF_RECORDS; ++i) {
        sprintf(records[i].name, "Name_%d", i + 1);
        sprintf(records[i].surname, "Surname_%d", i + 1);
        records[i].age = get_random_number(MIN_AGE, MAX_AGE);
    }

    // Открытие (создание) файла
    file = fopen(argv[1], "wb");
    if(file == NULL) {
        fprintf(stderr, "Error: file cannot be opened\n");
        return -1;
    }

    // Запись в файл
    fwrite(records, sizeof(struct record_s), AMOUNT_OF_RECORDS, file);
    
    // Закрытие файла
    fclose(file);

    printf("File '%s' is created, records: %d\n", argv[1], AMOUNT_OF_RECORDS);

    return 0;
}
