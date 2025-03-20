/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:07:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/20 12:33:49 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

bool ft_is_builtin(char *cmd_name)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (ft_strncmp(s1, s2, s1_len));
	else
		return (ft_strncmp(s1, s2, s2_len));
}

/*NOTE:
All builtins return an exit status of 2 to indicate incorrect usage, 
generally invalid options or missing arguments.*/

int		ft_exec_builtin(t_shell *shell, t_exec *exec_node)
{
	char *cmd_name;
	
	printf("test2\n");
	cmd_name = exec_node->command;
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
		ft_builtin_exit(shell, exec_node);
	return (ENO_NOT_FOUND);
}
