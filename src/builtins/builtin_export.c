/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:29:20 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*STEPS:
1 - NOTE: Options are not in the Minishell Subject!
2 - if just cmd without argos, put list shell.envp with msg “declare -x” (!including key with value=NULL)
3 - Loop argos:
	a- Check is key value valid. It should start with the letter or ‘_’, followed by letters, numbers, or ‘_’.Plus ‘=’ exists
	b- If key is not valid, error msg “not a valid identifier” and change exit code to 1.
	c- If key is valid create a new node t_env from input (key = , value = ). If no value, value = NULL
		- If key doesn't exist then add a new node t_env to shell.env;
		- if key exists then update env value;
*/

/*TO BE SOLVED:
- //alphabetic  order???
- append +=???*/


/*
TESTS:
export VAR
export | grep "VAR"

//VAR

export VAR=
export | grep "VAR"

//VAR=""

export VAR VAR
export VAR=10 VAR=5

export 2VAR
export VAR,>vh

export VAR,hs test=10
echo $? //1
export | grep test

*/

int ft_print_export_envp(t_list *env_list)
{
	
	t_list	*current;
	t_env	*env_entry;

	//check NULL? error???
	current = env_list;
	while (current)
	{
		env_entry = (t_env *)current->content;
		printf("declare -x %s", env_entry->key);
		if (env_entry->value != NULL)
			printf("=%s", env_entry->value);
		printf("\n");
		current = current->next;
	}
	return (ENO_SUCCESS);
}

bool	ft_is_env_key_valid(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (1);
}



int	ft_builtin_export(t_shell shell, t_exec *exec_node)
{
	int exit_code;
	char **export_args;
	t_env *existed_env;
	t_env *new_env;
	int i;

	i = 0;
	exit_code = ENO_SUCCESS;
	export_args = &(exec_node->av[1]);
	if (!export_args[0])
	{
		ft_print_export_envp(shell.envp);
		return (ENO_SUCCESS);
	}
	while (export_args[i])
	{
		if (ft_is_env_key_valid(*export_args) == false)
		{
			exit_code = ENO_GENERAL;
			ft_err_msg("export", export_args[i], "not a valid identifier");
		}
		else
		{
			new_env = ft_create_env_node(&shell, export_args[i]);
			if (ft_get_env(shell, new_env->key) == NULL)
				ft_lstadd_back(&shell.envp, ft_lstnew(new_env));			
			else
			{
				printf("key exists %s, update node t_env with new value %s\n", new_env->key, new_env->value);
				ft_update_env_value(shell.envp, new_env->key, new_env->value);
				ft_free_env_node(new_env);
			}
		}
		i ++;
	}
	return (exit_code);
}
