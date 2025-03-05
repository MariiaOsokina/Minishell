/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:22 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/05 13:01:27 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/structs.h"

/*
??check NULL?error??
1 - Loop the list of envp(parsed before);
2 - Check empty value???
3 - Print “key”=”value”
*/

/*TO BE SOLVED:
1- to be tested later with shell.envp (parsed list);
*/

int builtin_env(t_shell shell, t_node *cmd)
{
    
    t_list	*current;
	t_env	*env_entry;
    (void)cmd;

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
