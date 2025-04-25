/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:03:55 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 22:12:54 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*alphabetic  order???*/

static int	ft_print_export_envp(t_list *env_list)
{
	t_list	*current;
	t_env	*env_entry;

	current = env_list;
	while (current)
	{
		env_entry = (t_env *)current->content;
		printf("declare -x %s", env_entry->key);
		if (env_entry->value != NULL)
			printf("=\"%s\"", env_entry->value);
		printf("\n");
		current = current->next;
	}
	return (ENO_SUCCESS);
}

static bool	ft_is_env_key_valid(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (1);
}

static int	ft_export_with_args(t_shell *shell, char **export_args)
{
	t_env	*new_env;
	int		exit_code;

	exit_code = ENO_SUCCESS;
	while (*export_args)
	{
		if (!ft_is_env_key_valid(*export_args))
		{
			ft_err_msg("export", *export_args, "not a valid identifier");
			exit_code = ENO_GENERAL;
		}
		else
		{
			new_env = ft_create_env_node(shell, *export_args);
			if (ft_get_env_node(*shell, new_env->key) == NULL)
				ft_lstadd_back(&shell->envp, ft_lstnew(new_env));
			else
			{
				ft_update_env_value(shell->envp, new_env->key, new_env->value);
				ft_free_env_node(new_env);
			}
		}
		export_args++;
	}
	return (exit_code);
}

int	ft_builtin_export(t_shell *shell, t_exec *exec_node)
{
	int		exit_code;
	char	**export_args;

	exit_code = ENO_SUCCESS;
	export_args = &(exec_node->av[1]);
	if (!export_args[0])
	{
		ft_print_export_envp(shell->envp);
		return (ENO_SUCCESS);
	}
	exit_code = ft_export_with_args(shell, export_args);
	return (exit_code);
}
