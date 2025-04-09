/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:13:35 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/09 11:23:39 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	update_shlvl(t_shell shell)
// {
// 	t_list	*tmp;
// 	int		value;
// 	char	*n_val;

// 	tmp = shell.envp;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(((t_env *)tmp->content)->key, "SHLVL=") == 0)
// 			value = ft_atoi(((t_env *)tmp->content)->value);
// 			value++;
// 			n_val = ft_itoa(value);
// 			free(((t_env *)tmp->content)->value);
// 			((t_env *)tmp->content)->value = n_val;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

static void	ft_add_new_shlvl_env(t_shell shell)
{
	t_env	*new_shlvl_env;

	new_shlvl_env = ft_dup_env_node(&shell, "SHLVL", "1");
	ft_lstadd_back(&shell.envp, ft_lstnew(new_shlvl_env));
	return ;
}

void	ft_update_shlvl(t_shell shell)
{
	t_list	*tmp;
	int		value;
	char	*n_val;
	bool	shlvl_found;

	shlvl_found = false;
	tmp = shell.envp;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->content)->key, "SHLVL") == 0)
		{
			shlvl_found = true;
			value = ft_atoi(((t_env *)tmp->content)->value);
			value++;
			n_val = ft_itoa(value);
			free(((t_env *)tmp->content)->value);
			((t_env *)tmp->content)->value = n_val;
			printf("new shvlv %s\n", ((t_env *)tmp->content)->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (shlvl_found == false)
		ft_add_new_shlvl_env(shell);
}

int	g_signum;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	check_args(ac, av, envp);
	// env_lst(&shell, envp);
	ft_env_lst(&shell, envp);
	// print_env_lst(shell.envp);
	// update_shlvl(shell);
	ft_update_shlvl(shell);
	shell.exit_code = 0;
	terminal(&shell); // Ongoing..
	// free_env_lst(shell.envp);
	if (&shell.envp != NULL)
		ft_free_env_lst(&shell.envp);
	return (0);
}
