#include <netinet/in.h>
#include "sockets_functions.h"

void instructions();
int is_exist_file(char* filename);

int main() {
    
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    char server_addr[MAX_MESSAGE_LEN] = "";
    int sockfd;
    
    do {
    	puts("Enter server IP-address:");
    	rewind(stdin);
    	fgets(server_addr, MAX_MESSAGE_LEN, stdin);
    	server_addr[strlen(server_addr) - 1] = '\0';
    	client.sin_addr.s_addr = inet_addr(server_addr);
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    } while(Connect(sockfd,(struct sockaddr * )&client, sizeof(client)) == -1);


    char posibility_to_connect[MAX_MESSAGE_LEN] = "";
    recv(sockfd, posibility_to_connect, MAX_MESSAGE_LEN, 0); // получаем статус, можно ли подключаться к серверу или же сервер переполнен
    if(strcmp(posibility_to_connect, "NOT") == 0) {
    	puts("Server is currently overloaded and you cannot connect. Try later");
    	shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
    	return 0;
    }
    
    
    
    puts("You have successfully connected to the server.");
    puts("Enter messages and they will be sent to the server.");
    puts("Enter 'HELP' for help");

    char key[MAX_MESSAGE_LEN];
    char cur_dir[MAX_MESSAGE_LEN] = "";
    int repeat_flg = 1;

    while(repeat_flg == 1) {

        rewind(stdin);
        strcpy(key, "");
        printf("%s> ", cur_dir);
        fgets(key, MAX_MESSAGE_LEN, stdin);

        int command_file_size = -1;
        int i = 0;
        char** lines = NULL;

        if(strstr(key, "@") == key)
        {
            char line[MAX_MESSAGE_LEN] = "";
            strcpy(line, key+1);
            line[strlen(line) - 1] = '\0';
            if(is_exist_file(line) == 0)
            {
                fprintf(stdout, "Error: file not found\n");
                continue;
            }

            send(sockfd, key, MAX_MESSAGE_LEN, 0);
            command_file_size = 0;
            
            FILE* file;
            file = fopen(line, "rt");
            if(file != NULL) {
                while (fgets(line, MAX_MESSAGE_LEN, file)) { // Чтение строки из файла
                    send(sockfd, line, MAX_MESSAGE_LEN, 0);

                    lines = (char**)realloc(lines, sizeof(char*) * (command_file_size + 1));
                    lines[command_file_size] = (char*)malloc(sizeof(char)*256);
                    memcpy(lines[command_file_size], line, 256);
                    ++command_file_size;
                }
                send(sockfd, "0", MAX_MESSAGE_LEN, 0); // Конец чтения
                fclose(file); // Закрытие файла
            } else {
                puts("Error: cannot open file");
            }
        }

        do {
        
            char response[MAX_MESSAGE_LEN] = ""; 
            if(command_file_size > 0)
            {
                strcpy(key, lines[i++]);
                --command_file_size;
            } else if (command_file_size == 0) {
                for(;i>=0; --i)
                    free(lines[i]);
                free(lines);
                command_file_size = -1;
                break;
            }
            
            // Обработка запросов
            if(!strcmp(key, "HELP\n")) {
                instructions();

            } else if(!strcmp(key, "QUIT\n")) {
                if(command_file_size < 0)
                    send(sockfd, key, MAX_MESSAGE_LEN, 0);
                recv(sockfd, response, MAX_MESSAGE_LEN, 0); //response
                repeat_flg = 0;
                break;

            } else if(strstr(key, "ECHO") == key) {
                if(command_file_size < 0)
                    send(sockfd, key, MAX_MESSAGE_LEN, 0);
                recv(sockfd, response, MAX_MESSAGE_LEN, 0); //response
                printf("%s", response);

            } else if(!strcmp(key, "INFO\n")) {

                if(command_file_size < 0)
                    send(sockfd, key, MAX_MESSAGE_LEN, 0);
                recv_file(&sockfd, CLIENT_FILENAME);

                FILE* file;
                file = fopen(CLIENT_FILENAME, "rt");
                if(file != NULL)
                {
                    char buffer[1024] = "";
                    while(!feof(file))
                    {
                        fread(buffer, sizeof(char), 1024, file);
                        printf("%s", buffer);
                    }
                    fclose(file);
                }

            } else if(strstr(key, "CD") == key) {

                if(command_file_size < 0)
                    send(sockfd, key, MAX_MESSAGE_LEN, 0);
                
                recv(sockfd, response, MAX_MESSAGE_LEN, 0);
                if(strcmp(response, "NO") != 0) {
                    strcpy(cur_dir, response);
                } else {
                    fprintf(stderr, "Error: cannot change directory\n");
                }

            } else if(!strcmp(key, "LIST\n")) {

                if(command_file_size < 0)
                    send(sockfd, key, MAX_MESSAGE_LEN, 0);
                char size_str[16] = "";
                recv(sockfd, size_str, 16, 0);
                int size = atoi(size_str);
                char filename[MAX_MESSAGE_LEN] = "";
                for(int i = 0; i < size; ++i)
                {
                    recv(sockfd, filename, MAX_MESSAGE_LEN, 0);
                    printf("%s\n", filename);
                    strcpy(filename, "");
                }

            } else {
                fprintf(stderr, "Error: command not found\n");
            }
        } while(command_file_size > 0);
    }

    puts("The server disconnected you.");
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);

    return 0;
}


void instructions() {
	puts("\n'> ECHO [text]' -- эхо-запрос, возвращающий без изменений полученное от клиента\n"
		 "'> QUIT' -- запрос на завершение сеанса\n"
		 "'> INFO' -- запрос на получение информации о сервере\n"
		 "'> CD' -- изменить текущий каталог на сервере\n"
		 "'> LIST' -- вернуть список файловых объектов из текущего каталога\n"
		 "'> @[filename]' -- выполнить запросы из файла\n"
		 "'> HELP' -- список возможных запросов\n");		 
}


int is_exist_file(char* filename)
{
    FILE* f;
    f = fopen(filename, "r");
    if(f == NULL)
        return 0;
    fclose(f);
    return 1;
}

