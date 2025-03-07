/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:38:14 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/07 14:24:53 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*
1 - NOTE: Options are not in the Minishell Subject!
2 - If just cmd without argos, just return with exit code 0;
3 - Loop argos. 
4 - If arg is key in envp, unset this key=value, i.e. delete the node from list. 
5 - Check FREE properly (t_list, content, content->key, content->value) and reset ptrs to the next node.
*/

/*TO BE SOLVED
- delete node in list!!!*/

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
		if (ft_strcmp(env_content->key, key) == 0)
		{
			printf("test: key is here\n");
			if(prev_list)
				printf("test:  prev\n");
		// 		prev_list->next = current_list->next;
			else
				printf("test:  no prev\n");
		// 		shell.envp = current_list->next;
		// 	if (env_content)
		// 	{
				// if (env_content->value != NULL);
				// {
				// 	//env_content->value = NULL;
				// 	free(env_content->value);
				
				// }
				// if (env_content->key != NULL);
				// {
				// 	//env_content->key = NULL;
				// 	free(env_content->key);
				
				// }
		// 		free(env_content->key);
		// 		free(env_content);
		// 	}
		}
		prev_list = current_list; //??check
		// free(current_list);
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
