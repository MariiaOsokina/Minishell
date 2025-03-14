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

#include "../../includes/structs.h"

/*STEPS:
1 - NOTE: Options are not in the Minishell Subject!
2 - If just cmd without argos, just return with exit code 0;
3 - Loop argos. 
4 - If arg is key in envp, unset this key=value, i.e. delete the node from list. 
5 - Check FREE properly (t_list, content, content->key, content->value) and reset ptrs to the next node.
*/

/*TO BE SOLVED
- delete node in list!!!*/

char	*ft_unset_key(t_list *env_list, const char *key) // MO : should be key
{
	t_list	*current_list;
	t_list	*tmp_prev_list;
	t_env	*env_content;
	t_list	*tmp_next_list;

	tmp_prev_list = NULL;
	tmp_next_list = NULL;
	current_list = env_list;
	while (current_list)
	{
		tmp_next_list = current_list->next;
		env_content = (t_env *)current_list->content;
		if (ft_strcmp(env_content->key, key) == 0)
		{
			printf("test: key is %s here\n", env_content->key);
			if(tmp_prev_list)
			{
				printf("test:  prev\n");
				tmp_prev_list->next = current_list->next;
				current_list->next = NULL;
				ft_free_env_node(env_content);
				free(current_list);
				current_list = tmp_prev_list;
			}
			else
			{
				printf("test:  no prev\n");
				// tmp_next_list = current_list->next;
				// current_list->next = NULL;
				// ft_free_env_node(env_content);
				// free(current_list);

				// current_list = NULL;
				//SEGFAULT!!! NEEED TO BE TESTED!
				
			}
		}
		// printf("test: loop\n");
		tmp_prev_list = current_list;
		// printf("test: loop2\n");

		current_list = tmp_next_list;
		// printf("test: loop3\n");

	}
	return (NULL);
}

int ft_builtin_unset(t_shell shell, t_exec *exec_node)
{
	char **unset_args;
	int i;

	unset_args = &(exec_node->av[1]);
	i = 0;
	if (!unset_args[0])
		return (ENO_SUCCESS);
	while(unset_args[i])
	{
		ft_unset_key(shell.envp, unset_args[i]);
		i ++;
	}
	return (ENO_SUCCESS);
}
