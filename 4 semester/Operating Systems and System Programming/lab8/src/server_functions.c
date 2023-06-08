#include "server_functions.h"

void instructions(){
	puts("Menu:\n"
	     "m - Show menu\n" 
             "l - Show all clients\n"
             "q - Exit from server");
}


int what_to_do(char* key) {
	
    if(!strcmp(key, "QUIT\n")) {
      	return QUIT;        	     	
    } else if(strstr(key, "ECHO") == key) {
       	return ECHO;  	
    } else if(strstr(key, "@") == key) {
      	return FILE_COMMAND;    
    } else if(!strcmp(key, "INFO\n")) {
       	return INFO;   	
    } else if(strstr(key, "CD") == key) {
    	return CD;    	
    } else if(!strcmp(key, "LIST\n")) {
       	return LIST;    	
    } else {
      	return NOT_COMMAND;
    }
}


char* change_dir(char* root_dir, char* new_dir)                                                                   
{                                                                                                                                 
    DIR *dir_this = opendir(new_dir);  //открываем каталог                                                              
    if (!dir_this) {
    	fprintf(stderr, "Error: directory cannot be opened\n");                                                                                                                                                            
        return NULL;                                                                                                   
    }
    closedir(dir_this);
    
    char old_dir[MAX_MESSAGE_LEN] = "";
    if (getcwd(old_dir, sizeof(old_dir)) != NULL) {
        printf("Old working directory: %s\n", old_dir);
    } else {
        perror("getcwd() failed");
        exit(EXIT_FAILURE);
    } 
    
    if (chdir(new_dir) != 0) {
        perror("chdir() failed");
        return NULL;
    }       
    
    printf("Root directory: %s\n", root_dir);
    
    char new_work_dir[MAX_MESSAGE_LEN] = "";
    if (getcwd(new_work_dir, sizeof(new_work_dir)) != NULL) {
        printf("New prepared working directory: %s\n", new_work_dir);
    } else {
        perror("getcwd() failed");
        exit(EXIT_FAILURE);
    } 
     
    if(strstr(new_work_dir, root_dir) == NULL) {
    	if (chdir(old_dir) != 0) {
     	   perror("chdir() failed");
           return NULL;
    	}   
    	fprintf(stderr, "Error: Leaving the server's root directory tree is prohibited\n");
    	return NULL;
    }
        
    char* res = (char*)malloc(MAX_MESSAGE_LEN * sizeof(char));
    strcpy(res, new_work_dir + strlen(root_dir) + 1);
    return res;                                                                                                         
}


char* determine_type(const char* filename)                                                 
{             
	struct stat statbuf;
	lstat(filename, &statbuf);
	
	if(S_ISDIR(statbuf.st_mode)) {
		return "/";
        } else if(S_ISLNK(statbuf.st_mode)) {
        
        	char buf[MAX_MESSAGE_LEN];
        	int len = readlink(filename, buf, sizeof(buf)-1);
    		if (len == -1) {
        		perror("readlink() error");
        		return NULL;
    		}
    		char* res = (char*)malloc(MAX_MESSAGE_LEN * sizeof(char));
    		
    		struct stat tmp_st;
    		lstat(buf, &tmp_st);
    		if(S_ISLNK(tmp_st.st_mode)) {
    			strcpy(res, " -->> ");	
    		} else {
    			strcpy(res, " --> ");	
    		}
    		strcat(res, buf);
              	return res;
        } else if(S_ISREG(statbuf.st_mode)) {
               	return "";  //simple file
        } else {
               	return "(unknown type)";    
        }                                                                                                                                                         
}      


void add_to_file_names(char*** result, int size, char* path)  //добавление названия файла в результирующий массив
{
    *result = (char **)realloc(*result, sizeof(char *) * (size + 1));
    (*result)[size] = (char*)malloc(sizeof(char)*NAME_MAX);                                                  
    memcpy((*result)[size], path, NAME_MAX);                                                             
}


int read_directory(char*** result)                                                                   
{                                                                                                                     
    int size = 0;                   //здесь будет хранится размер массива имен файлов
    char dir_path[MAX_MESSAGE_LEN] = "";
    if (getcwd(dir_path, sizeof(dir_path)) != NULL) {
        printf("This directory path: %s\n", dir_path);
    } else {
        perror("getcwd() failed");
        exit(EXIT_FAILURE);
    }
                                  
    DIR *dir_this = opendir(dir_path);  //открываем каталог                                                              
    if (!dir_this) {                                                                               
        perror("Open error");                                                                                         
        return size;
    }  
                                                                                                                   
    char newPath[NAME_MAX+1];          //обновленный путь к файлам                                                     
    struct dirent* dir_entry;
    dir_entry = readdir(dir_this);                                                      
    while(dir_entry)
    {
        if (!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, "..")) {                                
            dir_entry = readdir(dir_this);
            continue;
                                                                                                                                                                                           
        }
        strcpy(newPath, "");                                                                                
        strcat(newPath, dir_entry->d_name);
        if (dir_entry) 
        {
            char tempPath[NAME_MAX+1] = "";
            strcpy(tempPath, newPath);
            char* file_type = determine_type(dir_entry->d_name);
            
            strcat(tempPath, file_type);  //добавляем к названию файла его тип
            add_to_file_names(result, size, tempPath);
            ++size;
            if(strstr(file_type, "-->") != NULL)
            	free(file_type); 
        }                                                                                                                                                                                                                                                                                                                                                                                                                   
        dir_entry = readdir(dir_this);                                                                                
    }
    closedir(dir_this);                                                                                               
    return size;                                                                                                         
}                        
