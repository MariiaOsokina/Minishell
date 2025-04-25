/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:39:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 20:21:57 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Alphabetical order??*/

int	ft_builtin_env(t_shell *shell, t_exec *exec_node)
{
	t_list	*current;
	t_env	*env_entry;

	(void)exec_node;
	current = shell->envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (env_entry->value != NULL)
			printf("%s=%s\n", env_entry->key, env_entry->value);
		current = current->next;
	}
	return (ENO_SUCCESS);
}
