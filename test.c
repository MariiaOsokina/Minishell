#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ft_sigint_noninteract_handler(int signum)
{
    (void)signum;
    write(1, "\nSIGINT received\n", 17);
}

void ft_siguit_noninteract_handler(int signum)
{
    (void)signum;
    write(1, "\nSIGQUIT received\n", 18);
}

void ft_signals_noninteractive(void)
{
    signal(SIGINT, ft_sigint_noninteract_handler);
    signal(SIGQUIT, ft_siguit_noninteract_handler);
}

int main(void)
{
    ft_signals_noninteractive();
    while (1) // Keep the program running to test signal handling
        pause();
    return 0;
}