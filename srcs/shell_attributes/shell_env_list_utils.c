/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:05:42 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/09 12:28:51 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_free_env_lst(t_list **envp)
// {
// 	ft_lstclear(envp, (void (*)(void *))ft_free_env_node);
// }

// void	ft_free_env_node(t_env *envp_node)
// {
// 	if (envp_node)
// 	{
// 		if (envp_node->key)
// 			free(envp_node->key);
// 		if (envp_node->value)
// 			free(envp_node->value);
// 		free(envp_node);
// 	}
// }

void	ft_free_env_node(void *envp)
{
	t_env	*envp_node;

	envp_node = (t_env *)envp;
	if (envp_node)
	{
		if (envp_node->key)
			free(envp_node->key);
		if (envp_node->value)
			free(envp_node->value);
		free(envp_node);
	}
}

//key and value are passed NOT malloced before
//check exit_failure for malloc of internal variables;

t_env	*ft_dup_env_node(t_shell *shell, char *key, char *value)
{
	t_env	*node;

	(void)shell;
	node = malloc(sizeof(t_env));
	if (!node)
		exit_failure(shell, "create_env_node");
	if (!key)
		exit_failure(shell, "no key");
	node->key = ft_strdup(key);
	if (value != NULL)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	return (node);
}

t_env	*ft_get_env_node(t_shell shell, char *target_key)
{
	t_list	*current_list;
	t_env	*env_content;

	current_list = shell.envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, target_key))
			return (env_content);
		current_list = current_list->next;
	}
	return (NULL);
}

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

void	ft_print_env_lst(t_list *lst) //for testing
{
	t_env	*env_var;

	while (lst)
	{
		env_var = (t_env *)lst->content;
		printf("%s='%s'\n", env_var->key, env_var->value);
		lst = lst->next;
	}
}
