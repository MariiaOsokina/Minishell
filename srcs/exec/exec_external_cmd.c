/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:44:24 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/30 00:24:52 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_cmd_is_dir(char *cmd_path)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd_path, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

static int	ft_check_access(char *cmd_path)
{
	if (access(cmd_path, F_OK) != 0)
	{
		ft_err_msg(cmd_path, "No such file or directory", NULL);
		return (ENO_NOT_FOUND);
	}
	else if (ft_cmd_is_dir(cmd_path))
	{
		ft_err_msg(cmd_path, "Is a directory", NULL);
		return (ENO_CANT_EXEC);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		ft_err_msg(cmd_path, "Permission denied\n", NULL);
		return (ENO_CANT_EXEC);
	}
	return (ENO_SUCCESS);
}

static void	ft_exec_with_path(t_shell *shell, t_exec *exec_node)
{
	char	*cmd_path;
	int		tmp_status;

	cmd_path = exec_node->av[0];
	tmp_status = ft_check_access(cmd_path);
	if (tmp_status != ENO_SUCCESS)
		ft_exit_with_full_cleanup(shell, tmp_status);
	else if (execve(cmd_path, exec_node->av, shell->envp_arr) == -1)
		ft_exit_with_full_cleanup(shell, ENO_GENERAL);
}

static void	ft_exec_from_env(t_shell *shell, t_exec *exec_node)
{
	char		*cmd_path;
	t_err_no	err_no;

	cmd_path = ft_get_env_path(*shell, exec_node->av[0], &err_no);
	if (err_no != ENO_SUCCESS)
		ft_exit_with_full_cleanup(shell, err_no);
	else if (execve(cmd_path, exec_node->av, shell->envp_arr) == -1)
	{
		free(cmd_path);
		ft_exit_with_full_cleanup(shell, ENO_GENERAL);
	}
}

int	ft_exec_external_cmd(t_shell *shell, t_exec *exec_node)
{
	int		tmp_status;
	int		fork_pid;

	tmp_status = 0;
	fork_pid = fork();
	if (fork_pid == 0)
	{
		tmp_status = ft_redirections(shell, exec_node);
		if (tmp_status != ENO_SUCCESS)
			ft_exit_with_full_cleanup(shell, tmp_status);
		if (ft_strnstr(exec_node->av[0], "/", ft_strlen(exec_node->av[0])))
			ft_exec_with_path(shell, exec_node);
		else
			ft_exec_from_env(shell, exec_node);
	}
	waitpid(fork_pid, &tmp_status, 0);
	return (ft_get_exit_status(tmp_status));
}
