/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:22 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/26 17:08:27 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//to be tested later with shell.envp (parsed list)
#include "../structs.h"

int builtin_env(t_shell shell, t_node *cmd)
{
    
    t_list	*current;
	t_env	*env_entry;

    //check NULL? error???
    current = shell.envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
        // if (env_entry->value != NULL) //if only key doesn't it print?
        printf("%s=%s\n", env_entry->key, env_entry->value);
        current = current->next;
	}
	return (ENO_SUCCESS);
}