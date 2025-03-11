#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define NAME_MAX 255

extern char **environ;

int is_valid_pid(pid_t);              //проверка pid
void get_child_path(char**, char**);  //получить указанный CHILD_PATH
void set_child_name(int, char**);     //дать имя процессу потомку
char** init_args(char*);              //инициализация командной строки для child
void change(char**, char**);          //поменять местами две строки
char** bubble_sort(char**);           //сортировка массива строк

int main(int argc, char* argv[], char* envp[]) {

    pid_t pid = 0;
    int child_status;
    char** args = init_args(argv[1]);
    char* child_path = (char*)malloc((NAME_MAX+1)*sizeof(char));
    char option;

    //Сортировка переменных среды.
    envp = bubble_sort(envp);
    for (int i = 0; envp[i] != NULL; ++i)
        puts(envp[i]);
    printf("\n");

    //Работа с процессами
    for (int i = 0; i < 100; ++i) {
        rewind(stdin);
        puts("Choose an option:\n'+'\n'*'\n'&'\nq - exit");
        option = getchar(); getchar();
        set_child_name(i, &args[0]);
        switch(option) {
        //Получение CHILD_PATH через функцию getenv();
        case '+':
            pid = fork();
            if(is_valid_pid(pid))
                execve(getenv("CHILD_PATH"), args, envp);
            wait(&child_status);
            break;
        //Получение CHILD_PATH через envp
        case '*':
            get_child_path(&child_path, envp);
            pid = fork();
            if(is_valid_pid(pid))
                execve(child_path, args, envp);
            wait(&child_status);
            break;
        //Получение CHILD_PATH через environ
        case '&':
            get_child_path(&child_path, environ);
            pid = fork();
            if(is_valid_pid(pid))
                execve(child_path, args, envp);
            wait(&child_status);
            break;
        //Выход из программы
        case 'q': 
            for (int i = 0; i < 3; ++i)
                free(args[i]);
            free(args);
            free(child_path);
            exit(0);
        //Выбор неправильной опции
        default:
            fprintf(stderr, "Error choosing option\n");
            break;
        }
    }
    //Очистка памяти
    for (int i = 0; i < 3; ++i)
        free(args[i]);
    free(args);
    free(child_path);
    return 0;
}

int is_valid_pid(pid_t pid)
{
     if (pid == -1) {
         fprintf(stderr, "Error occured: pid = -1\n");
         exit(-1);
     }
     if (pid == 0)
         return 1;
     return 0;
}

void get_child_path(char** child_path, char** env)
{
    for (int j = 0; env[j] != NULL; ++j) {
        if(strstr(env[j], "CHILD_PATH=") != NULL) {
            strcpy(*child_path, env[j]+11);
            return;
        }
    }
}

void set_child_name(int child_number, char** child_name)
{
    char tmp_child_number[3] = "";
    strcpy(*child_name, "CHILD_");
    sprintf(tmp_child_number, "%u", child_number);  //перевод числа в строку
    if (child_number < 10) 
        strcat(*child_name, "0");
    strcat(*child_name, tmp_child_number);
}

char** init_args(char* file_name)
{
    char** args =(char**)calloc(3, sizeof(char*));
    for (int i = 0; i < 3; ++i)
        args[i] = (char*)calloc(NAME_MAX, sizeof(char));
    strcpy(args[1], file_name);
    args[2] = NULL;
    return args;
}

void change(char **s1, char **s2) {
    char *temp = *s1;
    *s1 =  *s2;
    *s2 = temp;
}

char** bubble_sort(char** env)
{
    int size = 0;
    for (; env[size] != NULL; ++size);
    for (int i = 0; i < size; ++i) {
        for (int j = size-1; j > i; j--) {
            if (strcoll(env[j-1], env[j]) >= 0) {
                change(&env[j-1], &env[j]);
            }
        }
    }
    return env;
}
