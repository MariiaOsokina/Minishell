#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <signal.h>
#include <string.h>

int g_signal;

void sigint_handler(int signal, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	g_signal = signal;
}

void sigquit_handler(int signal, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	g_signal = signal;
}

int	function()
{
	//printf("Hello from rl_event_hook function ...\n");
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

int	main(void)
{
	struct sigaction sa;

	//sa.sa_handler = sigint_handler;
	sa.sa_sigaction = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART; //SA_RESTART is needed for correct tmp_status from execve in case of signals
	sigaction(SIGINT, &sa, NULL);

	sa.sa_sigaction = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);

	rl_event_hook = function;

	int input_numner = 0;
	printf("input number %d\n", input_numner);
	char *line = readline("prompt> ");
	while (line)
	{
		input_numner++;
		printf("input number %d\n", input_numner);
		line = readline("prompt> ");
		g_signal = -1;
	}
	return (0);
}
