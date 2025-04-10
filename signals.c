#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int g_signum;

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Parent: Received SIGUSR1 (Condition A)\n");
    } else if (sig == SIGUSR2) {
        printf("Parent: Received SIGUSR2 (Condition B)\n");
    } else {
        printf("Parent: Received unexpected signal %d\n", sig);
    }
}

if (signo == SIGINT)
g_signum = signo;
if (signo == SIGQUIT)
g_signum = signo;

void handle_child_signal(int signo) {
    if (signo == SIGUSR1)
        g_signum = SIGINT;
    else if (signo == SIGUSR2)
        g_signum = SIGQUIT;
}


void	ft_signals_child(void)
{
    signal(SIGUSR1, handle_child_signal);
    signal(SIGUSR2, handle_child_signal);

}

int main() {
    signal(SIGUSR1, handle_child_signal);
    signal(SIGUSR2, handle_child_signal);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        sleep(1);  // simulate work

        int condition = 2;  // this could be dynamic

        if (g_signum == SIGINT)
            kill(getppid(), SIGUSR1);
        if (signo == SIGQUIT)
            kill(getppid(), SIGUSR2);

        exit(0);
    } else {
        // Parent process
        printf("Parent waiting...\n");
        pause();  // wait for signal
        printf("Parent done.\n");
    }

    return 0;
}