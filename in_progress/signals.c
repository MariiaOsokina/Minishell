static void	ft_sigint_handler(int num)
{
	(void)num;
	if (g_minishell.signint_child)
	{
		ft_putstr_fd("\n", 1);
		g_minishell.signint_child = false;
		g_minishell.heredoc_sigint = true;
	}
	else //in parent
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
        //exit code = 130;
	}
}


void	ft_sigquit_handler(int num) //in execution, in not interactive mode;
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
    //exit_code = 131
}


void	ft_init_signals(void) //in parent ..
{
	struct termios	term;

	// term = g_minishell.original_term;
	// term.c_lflag &= ~ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);


	// g_minishell.heredoc_sigint = false;
	// g_minishell.signint_child = false;


	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}



// CTRL  + D has 3 effects
// if line is empty should be exit. check in readline!
		// g_minishell.line = readline(PROMPT);
		// if (!g_minishell.line)
		// 	(ft_clean_ms(),
		// 		ft_putstr_fd("exit\n", 1), exit(g_minishell.exit_s));

//in here_doc