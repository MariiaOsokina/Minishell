#include <minishell.h>

/*
	Minishell is not expecting any argument when programme is launched.
	Minishell is launched,
	then it provides a prompt for the user to write an input
*/
int	check_args(int ac, char **av, char **envp)
{
	(void) av;
	if (!envp || !*envp)
		ft_putendl_fd(RED "No envp: " DFLT, 2);
	if (ac > 1)
	{
		ft_putendl_fd(RED "Invalid input" DFLT, 2);
		exit(1);
	}
	return (0);
}
