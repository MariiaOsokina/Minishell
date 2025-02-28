/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:38:14 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/27 23:20:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"


char	*ft_unset_key(t_shell shell, const char *key) // MO : should be key
{
	t_list	*current_list;
	t_list	*prev_list;
	t_env	*env_content;

	prev_list = NULL;
	current_list = shell.envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, key))
		{
			if(prev_list)
				prev_list->next = current_list->next;
			else
				shell.envp = current_list->next;
			if (env_content)
			{
				free(env_content->value);
				free(env_content->key);
				free(env_content);
			}
		}
		prev_list = current_list; //??check
		free(current_list);
		current_list = current_list->next;
	}
	return (NULL);
}

int builtin_unset(t_shell shell, t_node *cmd)
{
	char **unset_args;
	int i;

	unset_args = &(cmd->expanded_args[1]);
	i = 0;
	if (!unset_args[0])
		return (ENO_SUCCESS);
	while(unset_args[i])
	{
		ft_unset_key(shell, unset_args[i]);
		i ++;
	}
	return (ENO_SUCCESS);
}

