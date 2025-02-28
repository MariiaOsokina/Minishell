/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:29:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/28 00:06:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

//in progress, needs to be tested

char	*get_value(t_shell *shell, char *env)
{
	char	*value;

	value = malloc(sizeof(char) * value_size(env) + 1);
	if (!value)
		exit_failure(shell, "env_value");
	ft_strlcpy(value, env, value_size(env) + 1);
	return (value);
}

char	*get_key(t_shell *shell, char *env)
{
	char	*key;

	key = malloc(sizeof(char) * content_size(env) + 1);
	if (!key)
		exit_failure(shell, "env_key"); //check malloc??
	ft_strlcpy(key, env, ft_strlen(env));
	return (key);
}


char	*ft_update_env_value(t_list *envp, const char *key) // MO : should be key
{
	t_list	*current_list;
	t_env	*env_content;

	current_list = envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, key)) //MO: ft_strcmp we can use here!!!
			return (env_content->value); //MO: not content, should be value;
        current_list = current_list->next;
	}
	return (NULL);
}

void	ft_get_env_value(t_shell shell, char *key, char *new_value)
{
	t_list	*current;
	t_env	*env_content;

	current = shell.envp;
	while (current)
	{
		env_content = (t_env *)current->content;
		if (!ft_strcmp(env_content->key, key))
		{
			if (new_value)
            {
                free(env_content->value);
                env_content->value = new_value;
            }
			return ;
		}
		current = current->next;
	}
	return ;
}


