/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:23:30 by aaladeok          #+#    #+#             */
/*   Updated: 2025/05/02 11:26:13 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_ands(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '&' || s[strlen(s) - 1] == '&')
		return (false);
	return (true);
}

bool	input_validation(t_shell *shell)
{
	if (!shell->input || shell->input[0] == '\0')
		return (true);
	shell->trimmed_input = ft_strtrim(shell->input, "\t ");
	if (!shell->trimmed_input)
		exit_failure(shell, "input_validation");
	if (shell->trimmed_input[0] == '\0' || shell->trimmed_input[0] == 32)
		return (true);
	if (!check_logical_or(shell->trimmed_input))
		return (syntax_error_msg(OR_ERROR), exit_code(shell, 2));
	if (!check_pipes(shell->trimmed_input))
		return (syntax_error_msg(PIPE_ERROR), exit_code(shell, 2));
	if (!check_ands(shell->trimmed_input))
		return (syntax_error_msg(AND_ERROR), exit_code(shell, 2));
	if (!check_quotes(shell->trimmed_input))
		return (syntax_error_msg(OPEN_QUOTE), exit_code(shell, 2));
	if (!check_redirections(shell->trimmed_input))
		return (exit_code(shell, 2));
	if (!check_parenthesis(shell->trimmed_input))
		return (exit_code(shell, 2));
	return (false);
}

bool	check_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (!quote)
				quote = str[i];
			else if (str[i] == quote)
				quote = 0;
		}
		i++;
	}
	return (quote == 0);
}

// bool	check_pipes(char *str)
// {
// 	int		i = 0;
// 	bool	in_single = false;
// 	bool	in_double = false;

// 	if (str[i] == '|' && str[i + 1] != '|')
// 		return (false);
// 	if (str[strlen(str) - 1] == '|')
// 		return (false);
// 	while (str[i])
// 	{
// 		toggle_quotes(str[i], &in_single, &in_double);
// 		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|')
// 			return (false);
// 		if (str[i] == '|' && str[i + 1] != '|' && !in_single && !in_double)
// 		{
// 			i++;
// 			while (is_space(str[i]))
// 				i++;
// 			if (str[i] == '|' && str[i + 1] != '|')
// 				return (false);
// 		}
// 		else
// 			i++;
// 	}
// 	return (true);
// }

bool	check_redirections(char *str)
{
	int	i;
	int	redir_char_len;

	i = 0;
	while (str[i])
	{
		i = jump_quotation(str, i);
		redir_char_len = is_redirect(&str[i]);
		if (redir_char_len > 0)
		{
			if (!handle_redir_error(str, &i, redir_char_len))
				return (false);
			if (!str[i])
			{
				syntax_error_msg(REDIR_ERROR);
				return (false);
			}
			continue ;
		}
		if (str[i])
			i++;
	}
	return (true);
}
