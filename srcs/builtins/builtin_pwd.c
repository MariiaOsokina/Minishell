/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:27:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/08 14:27:57 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*STEPS:
1 - Get cwd with getcwd (from unistd.h);
2 - Check error with getcwd
3 - Print cwd with “\n”;
4 - Don’t forget free as getcwd return char * allocated by malloc;
*/

/*
NOTES - TO BE TESTED/FIXED:
1 - variables PWD and shell.cwd can't be in conflict;
*/

int	ft_builtin_pwd(t_shell *shell, t_exec *exec_node)
{
	char	*cwd;

	(void)exec_node;
	(void)shell;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_err_msg("pwd", "cwd error", NULL);
		return (ENO_GENERAL);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (ENO_SUCCESS);
}
