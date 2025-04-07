/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:38:14 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*STEPS:
1 - NOTE: Options are not in the Minishell Subject!
2 - If just cmd without argos, just return with exit code 0;
3 - Loop argos. 
4 - If arg is key in envp, unset this key=value, i.e. delete the node from list. 
*/

// char *ft_unset_key(t_shell *shell, const char *key)
// {
//     t_list *current_list;
//     t_list *tmp_prev_list;
//     t_env *env_content;
//     t_list *to_free;

//     tmp_prev_list = NULL;
// 	to_free = NULL;
//     current_list = shell->envp;
//     while (current_list)
//     {
// 		env_content = (t_env *)current_list->content;

//         if (ft_strcmp(env_content->key, key) == 0)
//         {
//             if (tmp_prev_list)
//                 tmp_prev_list->next = current_list->next;
//             else //first element
//                 shell->envp = current_list->next; // Update the head of the list
//             to_free = current_list;
//             current_list = current_list->next;
// 			to_free->next=NULL;
// 			free(to_free);
//             continue ;  // Skip the rest of the loop after deletion
//         }
//         tmp_prev_list = current_list;
//         current_list = current_list->next;
//     }
//     return NULL;
// }


char *ft_unset_key(t_shell *shell, const char *key)
{
    t_list *current_list;
    t_list *tmp_prev_list;
    t_env *env_content;
    t_list *to_free;

    // to_free = NULL;
    tmp_prev_list = NULL;
    current_list = shell->envp;
    while (current_list)
    {
        env_content = (t_env *)current_list->content;

        if (ft_strcmp(env_content->key, key) == 0)
        {
            // Update the list pointers
            if (tmp_prev_list)
                tmp_prev_list->next = current_list->next;
            else
                shell->envp = current_list->next;
            ft_free_env_node(env_content);         
            // Free the node itself
            to_free = current_list;
            current_list = current_list->next;
            free(to_free);
            continue;
        }
        tmp_prev_list = current_list;
        current_list = current_list->next;
    }
    return (NULL);
}


int ft_builtin_unset(t_shell *shell, t_exec *exec_node)
{
	char **unset_args;
	int i;

	unset_args = &(exec_node->av[1]);
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


