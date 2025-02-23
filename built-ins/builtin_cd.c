/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:00:51 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/23 00:48:13 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
//#include "../../includes/minishell_flo.h"

int ft_arr_size(char **arr)
{
	//to be added;
	return (1);
}

int	builtin_cd(t_shell shell, t_node *cmd)
{
	char *path;

	path = cmd->expanded_args[1];
	if (ft_arr_size (cmd->expanded_args) > 2)
	{
		return (ft_err_msg("cd", "too many arguments", NULL), ENO_GENERAL);
	}
	else if (!path)
	{
		path = ft_get_envlst_val("HOME");
		if (!path)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
	}
	else if (ft_strcmp (path, "-") == 0)
	{
		path = ft_get_envlst_val("OLDPWD");
		if (!path)
			return (ft_err_msg("cd", "OLDPWD not set", NULL), ENO_GENERAL);
		ft_printf("%s\n", path);
	}
	if (chdir(path) != ENO_SUCCESS)
		return (ft_err_msg("cd", path, "No such file or directory"), ENO_GENERAL);
	//check if unset OLDPWD
	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	//check if unset PWD
	ft_update_envlst("PWD", getcwd(NULL, 0), false);
    return (ENO_SUCCESS);
}
