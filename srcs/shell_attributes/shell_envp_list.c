/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:54:33 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/06 11:50:26 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_env_lst(t_shell *shell, char **envp)
{
	int	i;

	t_env *env_content;
	shell->envp = NULL;
	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_content = ft_create_env_node(shell, envp[i]);
		if (!env_content)
			exit_failure(shell, "env_list");
		ft_lstadd_back(&shell->envp, ft_lstnew(env_content));
		i++;
	}
	return (NULL);
}

static char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (ft_strdup(str));
}

static char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_substr(str, i, ft_strlen(str) - i));
		}
		i++;
	}
	return (ft_strdup(""));
}

t_env	*ft_create_env_node(t_shell *shell, char *env)
{
	t_env	*node;
	(void)shell;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_failure(shell, "create_env_node");
	if (ft_strchr(env, '=') == NULL)
	{
		// printf("in %s  = not exists\n", env); //MO: for testing;
		node->key = ft_strdup(env);
		node->value = NULL;
	}
	else
	{
		// printf("in %s  = exists\n", env); //MO: for testing;
		node->key = ft_extract_key(env);
		node->value = ft_extract_value(env);		
	}
	return (node);
}
