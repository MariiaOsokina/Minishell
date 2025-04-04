#include "minishell.h"

void	update_shlvl(t_shell shell) //MO: need to be changed as doesn't change env_arr
{
	t_list	*tmp;
	int		value;
	char	*n_val;

	tmp = shell.envp;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->content)->key, "SHLVL") == 0) //MO: changed "SHLVL=" to "SHLVL"
		{
			
			value = ft_atoi(((t_env *)tmp->content)->value);
			printf(" shlvl %d\n", value);
			value++;
			printf("new shlvl %d\n", value);
			n_val = ft_itoa(value);
			free(((t_env *)tmp->content)->value);
			((t_env *)tmp->content)->value = n_val;
			break ;
		}
		tmp = tmp->next;
	}
}

int g_signum;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	check_args(ac, av, envp);
	// env_lst(&shell, envp);
	ft_env_lst(&shell, envp);
	// print_env_lst(shell.envp);
	update_shlvl(shell);
	shell.exit_code = 0;
	terminal(&shell); // Ongoing..
	// free_env_lst(shell.envp);
	ft_free_env_lst(&shell.envp);
	return (0);
}
