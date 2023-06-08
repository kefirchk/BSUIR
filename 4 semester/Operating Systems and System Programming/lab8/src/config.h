/*
 *
 *
 *       Configuration file
 *    for the server and client
 *
 *
*/


#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------
#define PORT 6655
#define MAX_SIZE_INT_STR 16
#define MAX_SIZE_STR 32
#define SERVER_FILENAME "/files/about_server"
#define CLIENT_FILENAME "./about_server"

#define MAX_CLIENT_SIZE 5   //максимальное число клиентов
#define BACKLOG 5
#define MAX_MESSAGE_LEN 512 //максимальная длина сообщения от клиента

//-----------------------------------------------

#endif // CONFIG_H

