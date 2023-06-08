#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define REPEATS 3  //количество повторений внешнего цикла

struct Pair
{
    int first;
    int second;
} pair;

sig_atomic_t alarm_signal;
int pair_count[4] = {0};
int permission_to_print = 1;
int stdout_is_free = 0;
int out_counter = 0;

//handlers:
void alarm_handler(int sig);
void stdout_handler(int signum, siginfo_t* info, void* uncontext_t);
void permission_handler(int signum, siginfo_t* info, void* ucontext_t);
void print_statistics();

int main(int argc, char* argv[]) {

    signal(SIGALRM, alarm_handler);
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;             
    act.sa_sigaction = permission_handler;
    sigaction(SIGUSR2, &act, NULL);
    act.sa_sigaction = stdout_handler;
    sigaction(SIGUSR1, &act, NULL);

    while (1) {
        alarm_signal = 0;
        if (out_counter >= REPEATS && permission_to_print == 1) {
            print_statistics();
        }
        alarm(2);
        int in_counter = 0;
        while (alarm_signal != 1) {
            switch (in_counter % 4) {
            case 0: pair.first = 0; pair.second = 0; in_counter = 0; break;
            case 1: pair.first = 0; pair.second = 1; break;
            case 2: pair.first = 1; pair.second = 0; break;
            case 3: pair.first = 1; pair.second = 1; break;
            }
            ++in_counter;
        }
        ++out_counter;
    }
    return 0;
}

void alarm_handler(int sig)
{
    if (pair.first == 0 && pair.second == 0) {
        ++pair_count[0];
    } else if (pair.first == 0 && pair.second == 1) {
        ++pair_count[1];
    } else if (pair.first == 1 && pair.second == 0) {
        ++pair_count[2];
    } else if (pair.first == 1 && pair.second == 1) {
        ++pair_count[3];
    }
    alarm_signal = 1;
    signal(SIGALRM, alarm_handler);
}

void stdout_handler(int signum, siginfo_t* info, void* uncontext_t)
{
    stdout_is_free = info->si_value.sival_int;
}
void permission_handler(int signum, siginfo_t* info, void* ucontext_t)
{
    if (info->si_value.sival_int == 'p') {
        stdout_is_free = 1;
        permission_to_print = 1;
        print_statistics();
        permission_to_print = 0;
    }
    else
        permission_to_print = info->si_value.sival_int;
    
}
void print_statistics()
{
    union sigval value;
    value.sival_int = getpid();
    while (stdout_is_free == 0) {
        sigqueue(getppid(), SIGUSR1, value);
        sleep(1);
    }
    printf("pid = %d, ppid = %d, {0, 0} = %d, {0, 1} = %d, {1, 0} = %d, {1, 1} = %d\n",
           getpid(), getppid(), pair_count[0], pair_count[1], pair_count[2], pair_count[3]);
    kill(getppid(), SIGUSR2);
    out_counter = 0;
    stdout_is_free = 0;
}

