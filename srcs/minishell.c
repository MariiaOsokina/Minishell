#include "minishell.h"

void	update_shlvl(t_shell shell)
{
	t_list	*tmp;
	int		value;
	char	*n_val;

	tmp = shell.envp;
	while (tmp)
	{
		// if (ft_strcmp(((t_env *)tmp->content)->key, "SHLVL=") == 0)
		if (ft_strcmp(((t_env *)tmp->content)->key, "SHLVL") == 0) //MO: added
		{
			value = ft_atoi(((t_env *)tmp->content)->value);
			value++;
			n_val = ft_itoa(value);
			free(((t_env *)tmp->content)->value);
			((t_env *)tmp->content)->value = n_val;
			break ;
		}
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	check_args(ac, av, envp);
	// env_lst(&shell, envp);
	ft_env_lst(&shell, envp);
	// print_env_lst(shell.envp);
	update_shlvl(shell);
	terminal(&shell, envp); // Ongoing..
	// free_env_lst(shell.envp);
	ft_free_env_lst(&shell.envp);
	return (0);
}
