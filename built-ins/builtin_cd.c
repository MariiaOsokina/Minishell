/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:00:51 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/28 01:11:15 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
//NOTE: update env_arr, envp, cwd ??? three places with the same values
static int ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i ++;
	return (i);
}

char	*ft_get_env_value(t_list *envp, const char *key)
{
	t_list	*current_list;
	t_env	*env_content;

	current_list = envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, key))
			return (env_content->value);
        current_list = current_list->next;
	}
	return (NULL);
}

//for export and cd
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

//in progress, needs to be tested

int	builtin_cd(t_shell shell, t_node *cmd)
{
	char *path;

	path = cmd->expanded_args[1];
	if (ft_arr_size (cmd->expanded_args) > 2) //arr should be with null terminator
	{
		return (ft_err_msg("cd", "too many arguments", NULL), ENO_GENERAL);
	}
	else if (!path)
	{
		path = ft_get_env_value(shell.envp, "HOME");
		if (!path)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
		printf("path home: %s\n", path);
	}
	// else if (ft_strcmp (path, "-") == 0)
	// {
	// 	path = ft_get_env_value("OLDPWD");
	// 	if (!path)
	// 		return (ft_err_msg("cd", "OLDPWD not set", NULL), ENO_GENERAL);
	// 	ft_printf("%s\n", path);
	// }
	if (chdir(path) != ENO_SUCCESS)
		return (ft_err_msg("cd", path, "No such file or directory"), ENO_GENERAL);
	//check if unset OLDPWD // ft_add_envlist
	ft_update_env_value(shell.envp, "OLDPWD", ft_get_env_value(shell.envp, "PWD"));
	//check if unset PWD // ft_add_envlist
	ft_update_env_value(shell.envp, "PWD", getcwd(NULL, 0));
    return (ENO_SUCCESS);
}
