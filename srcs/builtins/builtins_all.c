/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:07:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 20:27:49 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (!ft_strcmp(cmd_name, "echo")
		|| !ft_strcmp(cmd_name, "cd")
		|| !ft_strcmp(cmd_name, "exit")
		|| !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "env"))
		return (true);
	return (false);
}

int	ft_exec_builtin(t_shell *shell, t_exec *exec_node)
{
	char	*cmd_name;

	cmd_name = exec_node->av[0];
	if (!ft_strcmp(cmd_name, "echo"))
		return (ft_builtin_echo(shell, exec_node));
	else if (!ft_strcmp(cmd_name, "cd"))
		return (ft_builtin_cd(shell, exec_node));
	else if (!ft_strcmp(cmd_name, "export"))
		return (ft_builtin_export(shell, exec_node));
	else if (!ft_strcmp(cmd_name, "unset"))
		return (ft_builtin_unset(shell, exec_node));
	else if (!ft_strcmp(cmd_name, "env"))
		return (ft_builtin_env(shell, exec_node));
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (ft_builtin_pwd(shell, exec_node));
	else if (!ft_strcmp(cmd_name, "exit"))
		return (ft_exit_child(shell, exec_node));
	return (ENO_NOT_FOUND);
}
