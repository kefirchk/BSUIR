#include "server_functions.h"
#include <sys/wait.h>
                                                                                          
void* menu_handle(void*);
void* client_handle(void* client_n);
void show_clients();  // Функция отображения всех подключенных клиентов
void close_client(int client_number);  // Функция, отключающая определенного клиента

static char run_dir[MAX_MESSAGE_LEN] = ".";

int main(int argc , char *argv[]) {

    if(argv[1] != NULL) {
    	DIR *dir_this = opendir(argv[1]);  //открываем каталог                                                              
    	if (!dir_this) {
    		fprintf(stderr, "Error: directory cannot be opened\n");
    		return -1;
    	}
    	closedir(dir_this);
    
    	char old_dir[MAX_MESSAGE_LEN] = "";
    	if (getcwd(run_dir, sizeof(run_dir)) != NULL) {
        	printf("Running working directory: %s\n", run_dir);
    	} else {
        	perror("getcwd() failed");
        	exit(EXIT_FAILURE);
    	} 
    
    	if (chdir(argv[1]) != 0) {
        	perror("chdir() failed");
        	return -1;
    	}       
    
    	//printf("Root directory (main): %s\n", argv[1]);
    }
    
    
    
    
        
    int c, accept_result;
    struct sockaddr_in server, client;
    
    sockfd = Socket(AF_INET , SOCK_STREAM , 0); // сделали сокет и обработали ошибку
    
    server.sin_family = AF_INET;  // описали структуру сокета
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    
    for (int i = 0; i < MAX_CLIENT_SIZE; ++i) {
        connected_clients[i].is_closed = true;
    }
    
    Bind(sockfd,(struct sockaddr *)&server , sizeof(server)); // выполнили привязку
    
    Listen(sockfd, BACKLOG);       // прослушиваем
    
    c = sizeof(struct sockaddr_in);
    
    pthread_t thread_menu;     // поток для меню сервера
    pthread_create( &thread_menu , NULL , menu_handle , (socklen_t*)&sockfd);         // создаем меню в потоке
    
    puts("Server is running...");
    
    sleep(0.5);
    while (true) {
        
        accept_result = -1;
        puts("Waiting for connection...");
        accept_result = accept(sockfd, (struct sockaddr*)&client, (socklen_t*)&c);
        
        int pos = 0;
        for (int i = 0; i < MAX_CLIENT_SIZE; ++i) {  
            if (connected_clients[i].is_closed) {
                
                pos = i;
                break;
            }
        }
        
        connected_clients[pos].sock = accept_result;
        connected_clients[pos].id = pos;
        connected_clients[pos].client_addr = client;
        connected_clients[pos].is_closed = false;
        
        
        if (connected_clients[pos].sock < 0) {
            //perror("Connection accept error");
            break;
            
        } else if (thread_size + 1 > MAX_CLIENT_SIZE) {
            
            puts("New client connection attempt blocked.");
            puts("Connection limit exceeded.");
            send(connected_clients[pos].sock, "NOT", MAX_MESSAGE_LEN, 0);
            
        } else {
            
            send(connected_clients[pos].sock, "CAN", MAX_MESSAGE_LEN, 0);
            printf("Client №%d connected successfully\n", pos);
            pthread_create(&client_threads[thread_size] , NULL ,  client_handle, (void*)&pos);
            ++thread_size;
        }
    }
    return 0;
}
 
 
void *menu_handle(void *socketServ) {
    
    int sock = *(int*)socketServ;
    char key;
   
    instructions();
    while(1) {
   
        rewind(stdin);
        scanf("%s", &key);
        
        switch (key) {
            
            case 'm': { 
            	instructions(); 
            	break;
            }
            case 'l': {
                puts("List of clients:");
                show_clients();
                break;
            }
            case 'q': {
                puts("All clients are disabled. Server is off");
                for (int i = 0; i < MAX_CLIENT_SIZE; i ++) {
                    shutdown(connected_clients[i].sock, SHUT_RDWR);
                    close(connected_clients[i].sock);
                }
                
                for (int i = 0; i < MAX_CLIENT_SIZE; i ++) {
                   pthread_join(client_threads[i], NULL);
                }
                shutdown(sock,2);
                close(sock);
                return 0;
            }
            default:
            	fprintf(stderr, "Error: command not found\n");
            	break;
        }
    }
    return 0;
}


void *client_handle(void *client_n)
{
    int client_number = *(int *)client_n;
    char mess[MAX_MESSAGE_LEN]; // сообщение клиента    
    char root_dir[MAX_MESSAGE_LEN] = "";
    char cur_dir[MAX_MESSAGE_LEN] = "";
    
    if (getcwd(root_dir, sizeof(root_dir)) != NULL) {
        //printf("Root working directory: %s\n", root_dir);
    } else {
        perror("getcwd() failed");
        exit(EXIT_FAILURE);
    }
    strcpy(cur_dir, root_dir);
    
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        
    	while(!connected_clients[client_number].is_closed) {
   
    		strcpy(mess, "");
    		int recv_data = recv(connected_clients[client_number].sock, mess, MAX_MESSAGE_LEN, 0);
    
    		if (recv_data <= 0) {
    			printf("Error: received data size <= 0\n");
    			break;
    		}
        
    		printf("Client №%d sent: %s", connected_clients[client_number].id, mess);
    	
    		int key = what_to_do(mess);
    		char** commands = NULL;
    		char command[MAX_MESSAGE_LEN] = "";
    		int size = -1, i = 0;
    	
    		if(key == FILE_COMMAND) {
    			size = 0;
    			while(1) {
				recv(connected_clients[client_number].sock, command, MAX_MESSAGE_LEN, 0);
				if(strcmp(command, "0") == 0) {
					break;
				} else {
					commands = (char**)realloc(commands, sizeof(char*) * (size + 1));
    					commands[size] = (char*)malloc(sizeof(char)*MAX_MESSAGE_LEN);
    					strcpy(commands[size], command);
    					++size;
				}
			}
		}
    	
    		do {
    	
    		if(size > 0) {
    			key = what_to_do(commands[i]);
    			strcpy(mess, commands[i]);
    			++i;
    			--size;
    		} else if (size == 0) {
    			size = -1;
    			while(i >= 0)
    				free(commands[i--]);
    			free(commands);
    			break;
    		} 
    	
    	
    		switch(key)
    		{
			case NOT_COMMAND: {
				fprintf(stderr, "Error: command not found\n");	
				break;
			}
			case QUIT: {
				connected_clients[client_number].is_closed = true;
				size = -1;
				break;
			}
			case ECHO: {
				puts("do ECHO");
				send(connected_clients[client_number].sock, mess+5, MAX_MESSAGE_LEN, 0);
				break;
			}
			case INFO: {
				puts("do INFO");
				char path[MAX_MESSAGE_LEN];
				strcpy(path, run_dir);
				strcat(path, SERVER_FILENAME);
				FILE *f;
				f = fopen(path, "r");
				if(f == NULL) {
					fprintf(stderr, "No such file exists\n");
					exit(EXIT_FAILURE);
				}
    				send_file(&connected_clients[client_number].sock, path);
    				break;
			}
			case LIST: {
				puts("do LIST");
				char** dir_list = NULL;
				int size = read_directory(&dir_list);
				char size_str[16] = "";
				sprintf(size_str, "%d", size);
				send(connected_clients[client_number].sock, size_str, 16, 0);
		
				if(size == 0) {
					printf("Directory is empty\n");	
				} else {
					puts("List:");		
					for(int i = 0; i < size; ++i) {
						printf("%s\n", dir_list[i]);
						send(connected_clients[client_number].sock, *(dir_list+i), MAX_MESSAGE_LEN, 0);
					}
				}
			
				break;
			}
			case CD: {
				puts("do CD");
				char* new_dir = NULL;
				mess[strlen(mess)-1] = '\0';   //убираем \n в конце строки
				if((new_dir = change_dir(root_dir, mess+3)) == NULL) {
					puts("FAILURE: CANNOT OPEN DIR");
					send(connected_clients[client_number].sock, "NO", MAX_MESSAGE_LEN, 0);
				} else {
					puts("SUCCESS: OPEN DIR");
					getcwd(cur_dir, sizeof(cur_dir));
					printf("cur_dir=%s\n", cur_dir);
					send(connected_clients[client_number].sock, new_dir, MAX_MESSAGE_LEN, 0);
					free(new_dir);
				}
				break;
			}
		}
		} while(size > 0);
    	}
    	exit(0);
    } else {
    	int status;
    	waitpid(pid, &status, 0);
    }
    close_client(client_number);
    return 0;
}


void show_clients() {  // Функция отображения всех подключенных клиентов
    
    printf("Online: %d\n", thread_size);    
    for(int i = 0; i < MAX_CLIENT_SIZE; i ++) 
    {    
        if (!connected_clients[i].is_closed) 
        {
        	printf("Client №%d, address: %s %d\n", connected_clients[i].id, inet_ntoa(connected_clients[i].client_addr.sin_addr), 
        		htons(connected_clients[i].client_addr.sin_port));
        }
    }
}


void close_client(int client_number) {  // Функция, отключающая определенного клиента
    
    if(thread_size <= 0)
    {
    	fprintf(stderr, "Error: client cannot be disconnected, online=%d\n", thread_size);
    	return;
    }
    if(connected_clients[client_number].sock == -1)
    {
    	fprintf(stderr, "Error: there is no client with this id\n");
    	return;
    }
    
    --thread_size;
    
    shutdown(connected_clients[client_number].sock, SHUT_RDWR);
    close(connected_clients[client_number].sock);
    
    connected_clients[client_number].sock = -1;
    connected_clients[client_number].id = client_number;
    connected_clients[client_number].is_closed = true;
    
    pthread_join(client_threads[client_number], NULL);
    
    printf("Client №%d is disconnected. Online: %d\n", client_number, thread_size);
}



