#include "functions.h"

int main(int argc, char* argv[]) {

    char key[STRING_LENGTH];        // запрос
    struct stat file_statistics;    // файловая статистика

    struct record_s record_get;
    struct record_s mod_record;
    struct record_s new_record;
    struct record_s old_record;

    long unsigned int index_get = -1UL;

    // Проверка количества аргументов командной строки
    if(argc != 2) {
        fprintf(stderr, "Error: command line arguments are incorrect\n");
        printf("Format: ./main [имя_файла]\n");
        return -1;
    }

    // Открытие файла
    int fd = open(argv[1], O_RDWR);
    if(fd == -1){
        fprintf(stderr, "Error: file cannot be opened\n");
        return -1;
    }
    fstat(fd, &file_statistics);

    // Вывод меню
    instructions();
    while(1) {

        // Ввод опции
        rewind(stdin);
        strcpy(key, "");
        printf("> ");
        fgets(key, STRING_LENGTH, stdin);

        // Обработка запросов
        if(strcmp(key, "HELP\n") == 0) {
            instructions();
            
        } else if(strcmp(key, "LST\n") == 0) {
            if(set_lock(fd, F_RDLCK, SEEK_SET, 0, file_statistics.st_size) == -1) {
                puts("Файл уже блокирован другим процессом\n"
                    "Повторите запрос позже");
                continue;
            }

            lst_function(fd);

            if(set_lock(fd, F_UNLCK, SEEK_SET, 0, file_statistics.st_size) == -1) {
                puts("Ошибка: ошибка разблокировки файла");
            }

        } else if(strstr(key, "GET") == key) {
            index_get = atoi(key + 4);
            if(index_get <= 0 || index_get > file_statistics.st_size / sizeof(struct record_s)) {
                fprintf(stderr, "Error: incorrect index of record\n");
                index_get = -1;
                continue;
            }
            if(set_lock(fd, F_RDLCK, SEEK_SET, sizeof(struct record_s) * (index_get - 1), sizeof(struct record_s)) == -1) {
                puts("Файл уже блокирован другим процессом\n"
                    "Повторите запрос позже");
                continue;
            }

            record_get = get_function(fd, index_get);
            old_record = record_get;
            table_hat();
            printf("|%-3ld|%-15s|%-15s|%-6d|\n", index_get, record_get.name, record_get.surname, record_get.age);
            table_end();

            if(set_lock(fd, F_UNLCK, SEEK_SET, sizeof(struct record_s) * (index_get - 1), sizeof(struct record_s)) == -1) {
                puts("Ошибка: ошибка разблокировки файла");
            }

        } else if(strcmp(key, "MOD\n") == 0) {
            if(index_get == -1UL) {
                puts("Запись не выбрана");
                continue;
            }
            old_record = record_get;
            mod_record = record_get;
            char choice[STRING_LENGTH] = "";
            do {
                rewind(stdin);
                strcpy(choice, "");
                puts("Choose field:");
                puts("1 - name\n"
                     "2 - surname\n"
                     "3 - age\n"
                     "0 - <- BACK <-");
                fgets(choice, STRING_LENGTH, stdin);
                if(strcmp(choice, "1\n") == 0) {
                    puts("Enter new name:");
                    fgets(mod_record.name, STRING_LENGTH, stdin);
                    mod_record.name[strlen(mod_record.name) - 1] = '\0';
                
                } else if(strcmp(choice, "2\n") == 0) {
                    puts("Enter new surname:");
                    fgets(mod_record.surname, STRING_LENGTH, stdin);
                    mod_record.surname[strlen(mod_record.surname) - 1] = '\0';

                } else if(strcmp(choice, "3\n") == 0) {
                    puts("Enter new age:");
                    scanf("%hhu", &mod_record.age);

                } else if(strcmp(choice, "0\n") == 0) {
                    mod_record = old_record;
                    break;
                } else {
                    puts("Field is not exist");
                    continue;
                }
                break;
            } while(1);

            if(strcmp(choice, "0\n") == 0) {
                continue;
            }

            printf("Record №%ld:\n", index_get);
            table_hat();
            printf("|%-3ld|%-15s|%-15s|%-6d|\n", index_get, mod_record.name, mod_record.surname, mod_record.age);
            table_end();

        } else if(strcmp(key, "PUT\n") == 0) {
            if(index_get == -1UL) {
                puts("Запись не выбрана");
                continue;
            }
            if(memcmp(&old_record, &mod_record, sizeof(struct record_s)) != 0) {
               
                //printf("Record %ld has been modified\n", index_get);

                if(set_lock(fd, F_WRLCK, SEEK_SET, sizeof(struct record_s) * (index_get - 1), sizeof(struct record_s)) == -1) {
                    puts("Файл уже блокирован другим процессом\n"
                        "Повторите запрос позже");
                    continue;
                }
                struct record_s check_record = get_function(fd, index_get);
                if(memcmp(&old_record, &check_record, sizeof(struct record_s)) != 0) {
                    puts("Someone modified the record");
                    if(set_lock(fd, F_UNLCK, SEEK_SET, sizeof(struct record_s) * (index_get - 1), sizeof(struct record_s)) == -1) {
                        puts("Ошибка: ошибка разблокировки файла");
                    }
                    old_record = check_record;
                    printf("Record %ld:\n", index_get);
                    table_hat();
                    printf("|%-3ld|%-15s|%-15s|%-6d|\n", index_get, old_record.name, old_record.surname, old_record.age);
                    table_end();
                    
                    char option[STRING_LENGTH] = "";
                    do {
                        rewind(stdin);
                        puts("Save current changes?(y\\n)");
                        fgets(option, STRING_LENGTH, stdin);
                        if(strcmp(option, "n\n") == 0 ||
                            strcmp(option, "y\n") == 0) 
                        {
                            break;
                        }

                    } while(1);
                    if(strcmp(option, "n\n") == 0) {
                        mod_record = check_record;
                        continue;
                    }

                } 
                lseek(fd, sizeof(struct record_s) * (index_get - 1), SEEK_SET);
                write(fd, &mod_record, sizeof(struct record_s));
                if(set_lock(fd, F_UNLCK, SEEK_SET, sizeof(struct record_s) * (index_get - 1), sizeof(struct record_s)) == -1) {
                    puts("Ошибка: ошибка разблокировки файла");
                }
                printf("Record %ld has been updated\n", index_get);
                table_hat();
                printf("|%-3ld|%-15s|%-15s|%-6d|\n", index_get, mod_record.name, mod_record.surname, mod_record.age);
                table_end();
            } else {
                printf("Record %ld has not been modified\n", index_get);
            }

        } else if(strcmp(key, "QUIT\n") == 0) {
            break;

        } else {
            fprintf(stderr, "Error: command not found\n");
        }
    }

    // Закрытие файла
    close(fd);

    return 0;
}
