/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:25:38 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 20:18:27 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd_env(t_shell *shell, char *new_dir)
{
	t_env	*new_pwd_env;

	new_pwd_env = NULL;
	if (ft_get_env_node(*shell, "PWD") != NULL)
		ft_update_env_value(shell->envp, "PWD", new_dir);
	else
	{
		new_pwd_env = ft_dup_env_node(shell, "PWD", new_dir);
		ft_lstadd_back(&shell->envp, ft_lstnew(new_pwd_env));
	}
}

static void	ft_update_oldpwd_env(t_shell *shell, char *old_dir)
{
	t_env	*new_oldpwd_env;

	new_oldpwd_env = NULL;
	if (ft_get_env_node(*shell, "OLDPWD") != NULL)
		ft_update_env_value(shell->envp, "OLDPWD", old_dir);
	else
	{
		new_oldpwd_env = ft_dup_env_node(shell, "OLDPWD", old_dir);
		ft_lstadd_back(&shell->envp, ft_lstnew(new_oldpwd_env));
	}
}

static int	ft_change_dir(t_shell *shell, char *path)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (chdir(path) != ENO_SUCCESS)
	{
		free(old_dir);
		ft_err_msg("cd", path, "No such file or directory");
		return (ENO_GENERAL);
	}
	new_dir = getcwd(NULL, 0);
	ft_update_pwd_env(shell, new_dir);
	ft_update_oldpwd_env(shell, old_dir);
	if (old_dir)
		free(old_dir);
	if (new_dir)
		free(new_dir);
	return (ENO_SUCCESS);
}

int	ft_builtin_cd(t_shell *shell, t_exec *exec_node)
{
	char	*path;
	t_env	*home_env;

	path = exec_node->av[1];
	home_env = NULL;
	if (ft_arr_size(exec_node->av) > 2)
		return (ft_err_msg("cd", "too many arguments", NULL), ENO_GENERAL);
	else if (!path)
	{
		home_env = ft_get_env_node(*shell, "HOME");
		if (!home_env)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
		else
			path = home_env->value;
	}
	return (ft_change_dir(shell, path));
}
