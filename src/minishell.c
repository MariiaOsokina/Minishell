#include "minishell.h"

void	update_shlvl(t_shell shell)
{
	t_list	*tmp;
	int	value;
	char	*n_val;

	tmp = shell.envp;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->content)->value, "SHLVL=") == 0)
		{
			value = ft_atoi(((t_env *)tmp->content)->content);
			value++;
			n_val = ft_itoa(value);
			free(((t_env *)tmp->content)->content);
			((t_env *)tmp->content)->content = n_val;
			break;
		}
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	check_args(ac, av, envp);
	env_lst(&shell, envp);
	update_shlvl(shell);
	terminal(&shell, envp); //Ongoing..
	free_env(shell.envp);
	return 0;
}
