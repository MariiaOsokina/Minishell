/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:22:28 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 13:22:31 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code(t_shell *shell, int value)
{
	shell->exit_code = value;
	return (shell->exit_code);
}

char	*itoa_exit(t_shell *shell, char **str)
{
	char	*tmp;
	char	*code;

	code = ft_itoa(exit_code(shell, shell->exit_code));
	if (!code)
		exit_failure(shell, "itoa_exit");
	tmp = *str;
	*str = ft_strjoin(*str, code);
	free(tmp);
	free(code);
	if (!*str)
		exit_failure(shell, "itoa_exits");
	return (*str);
}

void	exit_failure(t_shell *shell, char *info)
{
	if (shell->envp != NULL)
		ft_lstclear(&shell->envp, ft_free_env_node);
	free_shell(shell);
	ft_putstr_fd(RED "malloc error: " DFLT, 2);
	ft_putendl_fd(info, 2);
	exit(1);
}
