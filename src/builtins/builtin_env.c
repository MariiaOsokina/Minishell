/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:22 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/structs.h"

/*STEPS:
1 - Loop the list of envp(parsed before);
2 - If value not empty print “key”=”value”
*/

/*
export MYVAR
env | grep "MYVAR" //env doesn't print if no value
export | grep "MYVAR" //export print w/o value

*/

/*Alphabetical order??*/

int ft_builtin_env(t_shell *shell, t_exec *exec_node)
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
