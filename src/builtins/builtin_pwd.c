/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:27:56 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/28 14:38:32 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"
//NOTE: two variables PWD and shell.cwd can't be in conflict//

int builtin_pwd(t_shell shell, t_node *cmd)
// int builtin_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);// malloc!!
	if (!cwd)
	{
		// err msg?
		return (ENO_GENERAL);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return (ENO_SUCCESS);
}
