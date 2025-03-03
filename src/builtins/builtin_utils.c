/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:29:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/03 01:53:29 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

//in progress, needs to be tested


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
			if (new_value)
            {
                free(env_content->value);
                env_content->value = ft_strdup(new_value); //chcek malloc issues;
            }
			return ;
		}
		current = current->next;
	}
	return ;
}

//for export and ?cd
int	ft_add_envlist(t_list *envp, char *key, char *value)
{
	ft_lstadd_back(envp, ft_lstnew(new_env_content(key, value))); // is back right//or alphabetic order??
	return (ENO_SUCCESS);
}