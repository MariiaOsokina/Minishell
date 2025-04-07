/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:05:42 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/07 14:15:54 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_extract_key(char *str);
// char	*ft_extract_value(char *str);
// void	*ft_env_lst(t_shell *shell, char **envp);
// t_env	*ft_create_env_node(t_shell *shell, char *env);
// t_env	*ft_dup_env_node(t_shell *shell, char *key, char *value);
// void	ft_print_env_lst(t_list *lst); //for testing
// void	ft_free_env_node(t_env *envp_node);
// void	ft_free_env_lst(t_list **envp);

// int	main(int ac, char **av, char **envp)
// {
// 	t_shell	shell;

//     ft_env_lst(&shell, envp);
// 	ft_print_env_lst(shell.envp);
// 	ft_free_env_lst(&shell.envp);
// 	return 0;
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	if (s1_len > s2_len)
// 		return (ft_strncmp(s1, s2, s1_len));
// 	else
// 		return (ft_strncmp(s1, s2, s2_len));
// }


void	ft_free_env_lst(t_list **envp)
{
	t_list	*tmp;
	t_env	*envp_node;

	while (*envp)
	{
		tmp = (*envp)->next;
		envp_node = (t_env *)(*envp)->content;
		ft_free_env_node(envp_node);
		free(*envp);
		*envp = tmp;
	}
	free(*envp);
	envp = NULL;
}

void	ft_free_env_node(t_env *envp_node)
{
		if (envp_node)
		{
			if(envp_node->key)
				free(envp_node->key);
			if(envp_node->value)
				free(envp_node->value);
			free(envp_node);
		}
}

t_env	*ft_dup_env_node(t_shell *shell, char *key, char *value) //key and value were NOT malloced before
{
	t_env	*node;
	(void)shell;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_failure(shell, "create_env_node"); //check malloc of internal variables;
	if (!key)
		exit_failure(shell, "no key"); //check malloc of internal variables;
	node->key = ft_strdup(key);
	if (value != NULL)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	return (node);
}

//in progress, needs to be tested
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

//for export and cd
void	ft_update_env_value(t_list *envp, char *key, char *new_value) //key and value were NOT malloced before
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

