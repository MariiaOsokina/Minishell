/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:27:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 20:27:15 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
