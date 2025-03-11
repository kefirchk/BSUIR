#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN 80     //maxlen for char buffer

// global values:
pid_t* child_pids = NULL;
int size_of_child_pids = 0;
int stdout_is_free = 1;

// additional functions:
void instructions();
void add_child();
void kill_child();
void kill_all_childs();
void list_of_processes();

//handlers:
void check_stdout_handler(int signum, siginfo_t *info, void* ucontext_t);
void waiting_handler(int sig);
void free_stdout_handler(int sig);

// main:
int main(int argc, char* argv[]) {

    char* option = (char*)malloc((MAX_LEN+1)*sizeof(char));
    int child_number;
    int child_status;

    struct sigaction act;
    union sigval value;
    act.sa_sigaction = check_stdout_handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act ,NULL);
    signal(SIGUSR2, free_stdout_handler);
    signal(SIGALRM, waiting_handler);

    puts("h - help\nEnter:");
    while (1) {
        rewind(stdin);
        strcpy(option, "");
        fgets(option, MAX_LEN, stdin);

        //Exec chosen option
        if (!strcmp(option, "h\n")) {         // h
            instructions();
        } else if (!strcmp(option, "+\n")) {  // +
            add_child();
        } else if (!strcmp(option, "-\n")) {  // -
            kill_child();
            printf("%d processes are still running\n", size_of_child_pids);
        } else if (!strcmp(option, "l\n")) {  // l
            list_of_processes();
        } else if (!strcmp(option, "k\n")) {  // k
            kill_all_childs();
        } else if (!strcmp(option, "s\n")) {  // s
            value.sival_int = 0;              // запрещаем вывод
            for(int i = 0; i < size_of_child_pids; ++i) 
                sigqueue(child_pids[i], SIGUSR2, value);
            printf("All child processes are blocked\n");   
        } else if (!strcmp(option, "g\n")) {  // g
            value.sival_int = 1;              // разрешаем вывод
            for(int i = 0; i < size_of_child_pids; ++i)
                sigqueue(child_pids[i], SIGUSR2, value);
            printf("All child processes are unblocked\n");
        } else if (option[0] == 's' && (child_number = atoi(option+1))) {  // s<num>
            if (child_number > 0 && child_number <= size_of_child_pids) {
                value.sival_int = 0;          // запрещаем вывод
                sigqueue(child_pids[child_number - 1], SIGUSR2, value);
                printf("Child C_%d is blocked\n", child_number);
            } else {
                fprintf(stdout, "error: process with given number does not exist\n");
            }
        } else if (option[0] == 'g' && (child_number = atoi(option+1))) {  // g<num>
            if (child_number > 0 && child_number <= size_of_child_pids) {
                value.sival_int = 1;          // разрешаем вывод
                sigqueue(child_pids[child_number - 1], SIGUSR2, value);
                printf("Child C_%d is unblocked\n", child_number);
            } else {
                fprintf(stdout, "error: process with given number does not exist\n");
            }
        } else if (option[0] == 'p' && (child_number = atoi(option+1))) {  // p<num>
            if (child_number > 0 && child_number <= size_of_child_pids) {     
                for(int i = 0; i < size_of_child_pids; ++i)
                {
                    if (i == child_number - 1) {
                        value.sival_int = 'p';
                        sigqueue(child_pids[child_number - 1], SIGUSR2, value);
                    } else {
                        value.sival_int = 0;  // запрещаем вывод
                        sigqueue(child_pids[i], SIGUSR2, value);
                    }
                }
                alarm(10);
            } else {
                fprintf(stdout, "error: process with given number does not exist\n");
            }
        } else if (!strcmp(option, "q\n")) {  // q
            kill_all_childs();
            free(option);
            return 0;
        }
    }
    return 0;
}

void waiting_handler(int sig)
{
    union sigval value;
	value.sival_int = 1;
    for(int i = 0; i < size_of_child_pids; ++i) {
       	sigqueue(child_pids[i], SIGUSR2, value);
   	}
    signal(SIGALRM, waiting_handler);
}

void free_stdout_handler(int signum)
{
    stdout_is_free = 1;
    signal(SIGUSR2, free_stdout_handler);
}

void check_stdout_handler(int signum, siginfo_t *info, void* ucontext_t)
{
    union sigval value;
	if(stdout_is_free == 1){
		value.sival_int = 1;
		sigqueue(info->si_value.sival_int, SIGUSR1, value);
		stdout_is_free = 0;
	} else {
		value.sival_int = 0;
		sigqueue(info->si_value.sival_int, SIGUSR1, value);
	}
}

void instructions()
{
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    puts("+ -- parent process P spawns child process C_k and reports it.\n\n"
         "- -- parent process P deletes the child C_k, reports this and the number of remaining ones.\n\n"
         "l -- list of parent and child processes is displayed.\n\n"
         "k -- P removes all C_k and reports it.\n\n"
         "s -- P prevents all C_k from outputting statistics.\n\n"
         "g -- P allows all C_k to output statistics.\n\n"
         "s<num> -- P prevents C_<num> from printing statistics.\n\n"
         "g<num> -- P allows C_<num> to print statistics.\n\n"
         "p<num> -- P denies all C_k output and asks C_<num> to print their statistics.\n"
         "After the specified time (5 s, for example), if the character 'g' is not entered, "
         "allows C_k to display statistics again.\n\n"
         "q -- P removes all C_k, reports it, and exits.");
    puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}

void add_child()
{
    pid_t new_pid = fork();
    if (new_pid) {
        ++size_of_child_pids;
        child_pids = (pid_t*)realloc(child_pids, size_of_child_pids*sizeof(pid_t));
        child_pids[size_of_child_pids - 1] = new_pid;
        printf("Child C_%d is created, pid=%d\n", size_of_child_pids, new_pid);
    } else if (new_pid == -1) {
        puts("error: child is not created");
    } else {
        char child_argv[20];
        sprintf(child_argv, "child C_%d", size_of_child_pids+1);
        execl("./child", child_argv, NULL);
    }
}

void kill_child()
{
    int status = -1;
    int child_status;
    if (size_of_child_pids > 0) { 
        status = kill(child_pids[--size_of_child_pids], SIGTERM);
        waitpid(child_pids[size_of_child_pids], &child_status, 0);
        if (status == -1) {
            fprintf(stderr, "error: kill returned -1\n");
            return;
        }
        child_pids = (pid_t*)realloc(child_pids, size_of_child_pids * sizeof(pid_t));
    } else {
        fprintf(stderr, "error: size of child array = 0\n");
        return;
    }
    printf("Child C_%d is succesfully killed\n", size_of_child_pids+1);
}
void kill_all_childs()
{
    for (int i = size_of_child_pids; i; --i)
        kill_child();
    printf("All childs are killed\n");
    free(child_pids);
    child_pids = NULL;
}

void list_of_processes()
{
    printf("Parent P, pid=%d\n", getpid());
    for (int i = 0; i < size_of_child_pids; ++i) {
        printf("Child C_%d, pid=%d\n", i+1, child_pids[i]);
    }
}
