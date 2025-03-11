#define _DEFAULT_SOURCE                                                                                               
#include <stdio.h>                                                                                                    
#include <sys/types.h>                                                                                               
#include <sys/stat.h>                                                                                        
#include <dirent.h>                                                                                                   
#include <stdlib.h>                                                                                                   
#include <errno.h>                                                                                                    
#include <string.h>                                                                                                   
#include <getopt.h>                                                                                                   
#include <unistd.h>                                                                                                   
                                                                                                                     
int checkFlags(unsigned char _type, int* flags);     //проверка флажков                                               
int dirwalk(char* path, int* flags, char*** result); //функция прохода по каталогам                                   
char* findPath(int argc, char* argv[]);              //поиск пути в массиве строк                                     
char* determine_type(unsigned char type_of_file);    //возвращает строку по типу файла                                
void change(char **s1, char **s2);                         //поменять местами строки 
void add_to_file_names(char*** result, int i, char* path);
                                                                                                                      
int main(int argc, char* argv[]){                                                                                     

    char path[NAME_MAX+1] = ".";   //указанный путь (по умолчанию равен каталогу, в котором находимся)              
    int flags[4] = {1, 1, 1, 0};   //массив опций(-f -d -l -s), инициализировано по умолчанию                         
    if(argc > 1)                                                                                                      
    {                                                                                                                 
        char* str = findPath(argc, argv);  //поиск возможного пути в параметрах командной строки                      
        if (str) {
            if (str[strlen(str) - 1] == '/')
                str[strlen(str) - 1] = '\0';
            strcpy(path, str);
        }                                                                                                             
        if (argc > 2 || !str) {    //установка опций для dirwalk'a                                                                                                                          
            int option;               
            for (int i = 0; i < 3; ++i)    //зануление флажков
                flags[i] = 0;
            while ((option = getopt(argc, argv, "-fdls")) != -1)
            {                                                                                                         
                switch(option) {                                                                                      
                case 'f': flags[0] = 1; break;  //проссмотр обычных файлов                                              
                case 'd': flags[1] = 1; break;  //проссмотр каталогов                                                   
                case 'l': flags[2] = 1; break;  //проссмотр симлинков                                                   
                case 's': flags[3] = 1; break;  //сортировка                                                            
                default: break;                                                                                       
                }                                                                                                     
            } 
            if (!flags[0] && !flags[1] && !flags[2]) {
                flags[0] = flags[1] = flags[2] = 1;
            }                                                                                                         
        }                                                                                                             
    }                                                                                                                                                                                                                                                      
    char **result = (char **)malloc(1 * sizeof(char *));   //массив имен файлов                                                           
    int size = dirwalk(path, flags, &result); 
                                                                            
    // Сортировка, если flags[3] = 1                                                                                  
    if (flags[3]) {                                                                                                   
        for (int i = 0; i < size; ++i) {                                                                              
            for (int j = size-1; j > i; j--) {                                                                        
                if (strcoll(result[j-1], result[j]) >= 0) {                                                           
                    change(&result[j-1], &result[j]);                                                                 
                }                                                                                                     
            }                                                                                                         
        }                                                                                                             
    }
    // Вывод массива с его одновременной очисткой                                                                                                                                                                                                                                      
    for (int i = 0; i < size; ++i) {                                                                                  
        printf("%s\n", result[i]);                                                                                    
        free(result[i]);                                                                                              
    }                                                                                                                 
    free(result);                                                                                                     
    return 0;                                                                                                         
}                                                                                                                     
                                                                                                                      
                                                                                                                      
int dirwalk(char* path, int* flags, char*** result)                                                                   
{                                                                                                                     
    static int i;                   //здесь будет хранится размер массива имен файлов                                 
    DIR *dir_this = opendir(path);  //открываем каталог                                                              
    if (!dir_this) {                                                                               
        perror("Open error");                                                                                         
        return i;                                                                                                                                                                                                    
    }                                                                                                                 
    char newPath[NAME_MAX+1];       //обновленный путь к файлам                                                     
    struct dirent* dir_entry;
    dir_entry = readdir(dir_this);                                                      
    while(dir_entry)
    {
        if (!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, "..")) {                                
            dir_entry = readdir(dir_this);                                                                            
            continue;                                                                                                                                                                               
        }
        strcpy(newPath, path);
        strcat(newPath, "/");                                                                                
        strcat(newPath, dir_entry->d_name);
        if (dir_entry) 
        {
            char tempPath[NAME_MAX+1];
            strcpy(tempPath, determine_type(dir_entry->d_type));  //добавляем к названию файла его тип
            strcat(tempPath, newPath);
            if (checkFlags(dir_entry->d_type, flags)) {  //если файл подходит по флажкам, то добавляем его в result
                add_to_file_names(result, i, tempPath);
                ++i; 
            }
            if (dir_entry->d_type == DT_DIR)             //открываем очередной каталог        
                dirwalk(newPath, flags, result);
        }                                                                                                                                                                                                                                                                                                                                                                                                                   
        dir_entry = readdir(dir_this);                                                                                
    }
    closedir(dir_this);                                                                                               
    return i;                                                                                                         
}                                                                                                                     
                                                                                                                      
                                                                                                                      
char* determine_type(unsigned char type_of_file)                                                 
{                                                                                                                     
    switch (type_of_file) {                                                                                           
    case DT_REG: return "\x1B[33mREG - \x1B[0m";  //REG (yellow)                                                  
    case DT_DIR: return "\x1B[31mDIR - \x1B[0m";  //DIR (red)                                                     
    case DT_LNK: return "\x1B[34mLNK - \x1B[0m";  //LNK (blue)                                                    
    default: return "\x1B[37mUNKNOWN - \x1B[0m";  //Unknown (white)                                               
    }                                                                                                                 
}                                                                                                                     
                                                                                                                      
int checkFlags(unsigned char _type, int* flags)   //проверка на флаги                                                                   
{
    switch (_type) {
    case DT_REG: return flags[0];
    case DT_DIR: return flags[1];
    case DT_LNK: return flags[2];
    default: return 0;
    }                                                                                                                                                                              
}                                                                                                                     
char* findPath(int argc, char* argv[])            //поиск в параметрах командной строки заданного пути                                                                      
{                                                                                                                     
    for (int i = 1; i < argc; ++i)                                                                                   
        if(strchr(argv[i], '/') || strchr(argv[i], '.'))                                                              
            return argv[i];                                                                                           
    return NULL;                                                                                                      
}                                                                                                                     
                                                                                                                      
void change(char **s1, char **s2) {               //функция меняет местами строки                                                                       
    char *temp = *s1;                                                                                                 
    *s1 =  *s2;                                                                                                       
    *s2 = temp;                                                                                                       
}
                                                                                                                  
                                                                                                                  
void add_to_file_names(char*** result, int i, char* path)  //добавление названия файла в результирующий массив
{
    *result = (char **)realloc(*result, sizeof(char *) * (i + 1));
    (*result)[i] = (char*)malloc(sizeof(char)*NAME_MAX);                                                  
    memcpy((*result)[i], path, NAME_MAX);                                                             
}
                                                                                                                     
