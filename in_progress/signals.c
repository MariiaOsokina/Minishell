/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:06:48 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/06 00:22:54 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/structs.h"

// NOTE: 
// - instead signal(SIGINT, reset_prompt) we can use sigaction(SIGINT, &s_sigact, 0) with struct signation.sa_handler ;

// MAN: the  behavior  of  signal() varies across UNIX versions, and has also varied historically across different versions of Linux.
// Avoid its use: use sigaction(2) instead.  See Portability below.
// - we can use tcsetattr??
	// struct termios	term;

	// term = g_minishell.original_term;
	// term.c_lflag &= ~ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
// - messages are STDERR messages;

/*
INTERACTIVE mode: in the main process (including saving heredoc) before execution:
CTRL+C (SIGINT)displays a new prompt on a new line.
CTR+\ (SIGQUIT) does nothing
*/

void ft_sigint_handler_int(void)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//exit code 130;
	//exit(130); ???
}

void ft_signal_interact(void)
{
	signal(SIGINT, ft_sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
}

/*ctrl-D exits the shell.*/
// readline() can help with checking for EOF. 
//When using readline, if the user inputs Ctrl + D, readline will return NULL. You can check for this in your code to handle EOF.



// if line is empty should be exit. check in readline!
		// line = readline(PROMPT);
		// if (!line)
		// {
		// 	ft_clean();
		// 	ft_putstr_fd("exit\n", 1);
		// 	exit(minishell.exit_s);
		// }
		/*
NONINTERACTIVE mode - execuction:
CTRL+C (SIGINT) -> quit process and print "^C" with a \n
CTR+\ (SIGQUIT) -> quit process and print "^\Quit (core dumped)"
*/

void	ft_sigquit_handler(void)
{
	ft_putstr_fd(STDERR_FILENO, "Quit (core dumped)\n");
	rl_on_new_line();
	//exit code 131 // handles via waitpid() and ft_get_exit_status();
}

void ft_sigint_handler_nonint(void)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	//exit code 130 // handles via waitpid() and ft_get_exit_status();
}

void ft_sigint_handler_heredoc(void)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//exit code 130;
	//exit(130); ???
}


void signal_noniteract(void)
{
	signal(SIGINT, ft_sigint_handler_nonint);
	signal(SIGQUIT, ft_sigquit_handler);
}

/*
HEREDOC + SIGNALS:
CTRL+C (SIGINT) -> 
	(1)	ft_clean(); 
	(2) print ""^C" with a \n"; 
	(3) exit(2), i.e. quit process as readline inside child process;
	(4) exit code 130 // handles via waitpid() and ft_get_exit_status(); ??? 
	(5) if 130 then "continue", move to the next interaction in while();

CTR+\ (SIGQUIT) -> quit process and print "^\Quit (core dumped)", the same as the main and inhereted by parent;

CTRL+ D (EOF) -> check EOF(return readline() is NULL), print msg to STDERR and exit

		line = readline('>');
		if (!line)
		{
				ft_putstr_fd(STDERR, "\nbash: warning: here-document at line 16 delimited by end-of-file (\'")
				ft_putstr_fd(STDERR, delimeter);
				ft_putstr_fd(STDERR, "\')\n");
				break;
		}
cat <<e1 <<e2 >outfile
> test1
> 
bash: warning: here-document at line 15 delimited by end-of-file (wanted `e1') // this message should be in STDERR!
> test2test
> 
bash: warning: here-document at line 16 delimited by end-of-file (wanted `e2')
*/
