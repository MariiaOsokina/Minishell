/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:29:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/25 00:56:47 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//in progress, needs to be tested
t_env	*ft_get_env(t_shell shell, char *check_key)
{
	t_list	*current_list;
	t_env	*env_content;
	
	current_list = shell.envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, check_key))
			return (env_content);
        current_list = current_list->next;
	}
	return (NULL);
}

//for export and cd
void	ft_update_env_value(t_list *envp, char *key, char *new_value)
{
	t_list	*current;
	t_env	*env_content;

	current = envp;
	while (current)
	{
		env_content = (t_env *)current->content;
		if (!ft_strcmp(env_content->key, key))
		{
			if (env_content->value)
			{
				free(env_content->value);
				env_content->value = NULL;
			}
			if (new_value)
				env_content->value = ft_strdup(new_value);
			else
				env_content->value = NULL;
			return ;
		}
		current = current->next;
	}
	return ;
}

int ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i ++;
	return (i);
}