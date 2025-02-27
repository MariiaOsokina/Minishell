/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:29:20 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/27 14:26:58 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int ft_put_export_envp(t_shell shell, t_node *cmd)
{
	
	t_list	*current;
	t_env	*env_entry;

	//check NULL? error???
	current = shell.envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		// if (env_entry->value != NULL) //if only key doesn't it print?
		printf("declare -x %s=\"", env_entry->key);
		//add
		current = current->next;
	}
	return (ENO_SUCCESS);
}

bool ft_is_key_valid(char *arg)
{
	return (true);
}

int	builtin_export(t_shell shell, t_node *cmd)
{
	int exit_code;
	char **export_args;
	int i;
	char *key;
	
	exit_code = ENO_SUCCESS;
	export_args = &(cmd->expanded_args[1]);
	i = 0;

	if (!export_args[0])
	{
		ft_put_export_envp(shell, cmd);
		return (ENO_SUCCESS);
	}
	while (export_args[i])
	{
		if (ft_is_key_valid(export_args[i]) == false)
		{
			exit_code = STDERR_FILENO;
			ft_err_msg("exit", cmd->expanded_args[i], "not a valid identifier\n");
		}
		else
		{
			// key = ft_extract_key(argv[i]);
			// if (ft_env_entry_exists(key))
			// 	ft_update_envlst(key, ft_extract_value(argv[i]), false);
			// else
			// 	ft_update_envlst(key, ft_extract_value(argv[i]), true);
		}
		i ++;
	}
	return (exit_code);
}
