/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:01:22 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/11 00:36:29 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* MACROS WEXITSTATUS shifts to bits to right place,  
as child exit status is stored in the higher bits.
*/

// int	ft_get_exit_status(int status)
// {
// 	if (WIFSIGNALED(status))
// 	{
// 		if (WTERMSIG(status) == SIGINT)
// 			kill(getppid(), SIGUSR1);
// 		if (WTERMSIG(status) == SIGQUIT)
// 			kill(getppid(), SIGUSR2);
// 		return (128 + WTERMSIG(status));
// 	}
// 	return (WEXITSTATUS(status));
// }

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

//function for printing an error message to STDERR

void	ft_err_msg(char *s1, char *s2, char *s3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
		if (s3)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(s3, STDERR_FILENO);
		}
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	return ;
}

void	ft_free_full_shell(t_shell *shell)
{
	if (shell->envp != NULL)
		// ft_free_env_lst(&(shell)->envp);
		ft_lstclear(&shell->envp, ft_free_env_node);
	free_shell(shell);
}

void	ft_exit_with_full_cleanup(t_shell *shell, int status)
{
	ft_free_full_shell(shell);
	exit(status);
}
