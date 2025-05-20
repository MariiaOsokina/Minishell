/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:45:01 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/16 23:50:24 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This is called by the terminal to prep env variables*/
static int	count_valid_env_entries(t_list *envp_list)
{
	int		count;
	t_env	*env_content;

	count = 0;
	while (envp_list)
	{
		env_content = (t_env *)envp_list->content;
		if (env_content && env_content->value != NULL)
			count++;
		envp_list = envp_list->next;
	}
	return (count);
}

static char	*create_env_string(t_env *env_content)
{
	char	*key_with_equals;
	char	*full_string;

	if (!env_content->key)
		return (NULL);
	key_with_equals = ft_strjoin(env_content->key, "=");
	if (!key_with_equals)
		return (NULL);
	full_string = ft_strjoin(key_with_equals, env_content->value);
	free(key_with_equals);
	if (!full_string)
		return (NULL);
	return (full_string);
}

static char	**init_env_arr(t_shell *shell, t_list *envp_list, int *count)
{
	char	**env_arr;

	*count = count_valid_env_entries(envp_list);
	env_arr = malloc(sizeof(char *) * (*count + 1));
	if (!env_arr)
		exit_failure(shell, "env_arr");
	return (env_arr);
}

char	**ft_env_arr(t_shell *shell, t_list *envp_list)
{
	char	**env_arr;
	int		count;
	int		i;
	t_env	*env_content;
	char	*env_string;

	env_arr = init_env_arr(shell, envp_list, &count);
	i = 0;
	while (envp_list && i < count)
	{
		env_content = (t_env *)envp_list->content;
		if (env_content && env_content->value != NULL)
		{
			env_string = create_env_string(env_content);
			if (!env_string)
			{
				ft_free_str_arr(env_arr, i);
				exit_failure(shell, "env_arr_string");
			}
			env_arr[i++] = env_string;
		}
		envp_list = envp_list->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
