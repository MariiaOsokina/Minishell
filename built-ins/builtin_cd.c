/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:00:51 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/25 14:03:46 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
//#include "../../includes/minishell_flo.h"

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

//in progress, needs to be tested

static char	*sh_get_env(t_list *envp, const char *key) // MO : should be key
{
	t_list	*current;
	t_env	*env_entry;

	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (!ft_strcmp(env_entry->key, key)) //MO: ft_strcmp we can use here!!!
			return (env_entry->value); //MO: not content, should be value;
		current = current->next;
	}
	return (NULL);
}

//in progress, needs to be tested


static void	sh_update_env(t_list *envp, char *key, char *value, bool create)
{
	t_list	*current;
	t_env	*env_entry;

	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (!ft_strcmp(env_entry->key, key))
		{
			if (value)
				env_entry->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		current = current->next;
	}
	// if (create)
	// 	ft_envlst_back(ft_envlst_new(key, value));
	return ;
}


// void	*ft_garbage_collector(void *ptr, bool clean)
// {
// 	static t_list	*garbage_list;

// 	if (clean)
// 	{
// 		ft_lstclear(&garbage_list, ft_del);
// 		return (NULL);
// 	}
// 	else
// 	{
// 		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
// 		return (ptr);
// 	}
// }

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
		path = sh_get_env(shell.envp, "HOME");
		if (!path)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
		printf("path home: %s\n", path);
	}
	// else if (ft_strcmp (path, "-") == 0)
	// {
	// 	path = ft_get_envlst_val("OLDPWD");
	// 	if (!path)
	// 		return (ft_err_msg("cd", "OLDPWD not set", NULL), ENO_GENERAL);
	// 	ft_printf("%s\n", path);
	// }
	if (chdir(path) != ENO_SUCCESS)
		return (ft_err_msg("cd", path, "No such file or directory"), ENO_GENERAL);
	printf("cur dir %s\n", getcwd(NULL, 0)); // for testing, to be deleted
	//check if unset OLDPWD
	sh_update_env(shell.envp, "OLDPWD", sh_get_env(shell.envp, "PWD"), false);
	//check if unset PWD
	sh_update_env(shell.envp, "PWD", getcwd(NULL, 0), false);
    return (ENO_SUCCESS);
}
