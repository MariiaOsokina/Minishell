/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:12:10 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/29 17:12:20 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_input(t_shell *shell)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;
	char	*code;
	char	*prompt;

	code = ft_itoa(exit_code(shell, shell->exit_code));
	cwd = getcwd(NULL, 0);
	prompt = ESC_START PROMPT ESC_RESET;
	tmp = ft_strjoin(prompt, code);
	free(code);
	if (!tmp)
		exit_failure(shell, "shell_input");
	tmp2 = ft_strjoin(tmp, ESC_CODE);
	free(tmp);
	if (!tmp2)
		exit_failure(shell, "shell_input");
	tmp = ft_strjoin(tmp2, cwd);
	free(tmp2);
	if (!tmp)
		exit_failure(shell, "shell_input");
	shell->cwd = ft_strjoin(tmp, ARROW);
	free(cwd);
	free(tmp);
}
