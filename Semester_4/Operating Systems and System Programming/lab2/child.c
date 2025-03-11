#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 80                    //максимальная длина строки

int main(int argc, char *argv[], char *envp[]) {

    char buffer[MAX_LEN+1];           //очередной параметр из файла
    char parameter[MAX_LEN+1];        //название переменной из envp
    char* end;
    FILE* file = NULL;                //наш рабочий файл, по умолчанию - "vars"
    file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "File opening error '%s'\n", argv[1]);
        exit(-1);
    } 
    printf("\nName=%s\nPID=%u\nPPID=%u\n", argv[0], getpid(), getppid());
    while (1) {
        fgets(buffer, MAX_LEN, file); //читаем файл
        if (feof(file))               //если конец файла
            break;
        if (buffer[strlen(buffer) - 1] == '\n')      //убираем из строки \n
            buffer[strlen(buffer) - 1] = '\0';
        for (int i = 0, j; envp[i] != NULL; ++i) {   //вывод переменных файла из среды
            end = strchr(envp[i], '=');
            for (j = 0; envp[i]+j != end; ++j)       //переписывание названия переменной
                parameter[j] = envp[i][j];
            parameter[j] = '\0';
            if (!strcmp(parameter, buffer)) {        //если переменные совпадают,
                puts(envp[i]);                       //то выводим
                break;
            }
        }
    }
    fclose(file);                     //закрываем файл
    puts("");
    exit(0);
}
