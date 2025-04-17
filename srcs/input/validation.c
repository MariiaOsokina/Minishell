#include "minishell.h"

#include "minishell.h"

/*
	This function is validating shell user input,
	may require extra functions for valid env input checks.
	e.g. $VAR and ${VAR}
*/
bool	input_validation(t_shell *shell)
{
	if (!shell->input || shell->input[0] == '\0')
		return (true);
	shell->trimmed_input = ft_strtrim(shell->input, "\t ");
	if (!shell->trimmed_input)
		exit_failure(shell, "input_validation");
	if (shell->trimmed_input[0] == '\0')
		return (true); //new line
	if (!check_pipes(shell->trimmed_input))
		return (syntax_error_msg(PIPE_ERROR), exit_code(2));
	if (!check_quotes(shell->trimmed_input))
		return (syntax_error_msg(OPEN_QUOTE), exit_code(2));
	if (!check_redirections(shell->trimmed_input))
		return (exit_code(2));
	if (!check_parenthesis(shell->trimmed_input))
		return (exit_code(2));
	if (!check_line_len(shell->trimmed_input))
		return (exit_code(2));
	return (false);
}

/*
	validation.c
	Checks for closed quotes
*/
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
	return (quote == 0); // Returns true if all quotes are closed.
}

/*
	Check_pipes check for placement of pipes in command strings,
	checks for pipes in quotes and ignores them.
	It returns true or false if placement of pipes are correct or incorrect.
*/
bool	check_pipes(char *str)
{
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (str[i] == '|' || str[strlen(str) - 1] == '|')
		return (false);
	while (str[i])
	{
		toggle_quotes(str[i], &in_single_quote, &in_double_quote);
		if (str[i] == '|' && !in_single_quote && !in_double_quote)
		{
			while (is_space(str[++i]))
				;
			if (str[i] == '|' && str[i - 1] != '|')
				return (false);
		}
		i++;
	}
	return (true);
}

/*
	Location: validation.c
	This returns true if there are redirections in the command for execution
*/
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



// /*
// 	This function is validating shell user input,
// 	may require extra functions for valid env input checks.
// 	e.g. $VAR and ${VAR}
// */

// bool	input_validation(t_shell *shell) //MO: new version from Adewale at 2 April
// {
// 	if (!shell->input || shell->input[0] == '\0')
// 		return (true);
// 	shell->trimmed_input = ft_strtrim(shell->input, "\t ");
// 	if (!shell->trimmed_input) //MO: what is this case??
// 		exit_failure(shell, "input_validation");
// 	if (!check_pipes(shell->trimmed_input))
// 		return (syntax_error_msg(PIPE_ERROR), exit_code(2), false);
// 	if (!check_quotes(shell->trimmed_input))
// 		return (syntax_error_msg(OPEN_QUOTE), exit_code(2), false);
// 	if (!check_redirections(shell->trimmed_input))
// 		return (exit_code(2), false);
// 	if (!check_parenthesis(shell->trimmed_input))
// 		return (exit_code(2), false);
// 	if (!check_line_len(shell->trimmed_input))
// 		return (exit_code(2), false);
// 	return (true);
// }



// /*
// 	validation.c
// 	Checks for closed quotes
// */
// bool	check_quotes(char *str)
// {
// 	int		i;
// 	char	quote;

// 	i = 0;
// 	quote = 0;
// 	while (str[i])
// 	{
// 		if (is_quote(str[i]))
// 		{
// 			if (!quote)
// 				quote = str[i];
// 			else if (str[i] == quote)
// 				quote = 0;
// 		}
// 		i++;
// 	}
// 	return (quote == 0); // Returns true if all quotes are closed.
// }

// /*
// 	Check_pipes check for placement of pipes in command strings,
// 	checks for pipes in quotes and ignores them.
// 	It returns true or false if placement of pipes are correct or incorrect.
// */
// bool	check_pipes(char *str)
// {
// 	int		i;
// 	bool	in_single_quote;
// 	bool	in_double_quote;

// 	i = 0;
// 	in_single_quote = false;
// 	in_double_quote = false;
// 	if (str[i] == '|' || str[strlen(str) - 1] == '|')
// 		return (false);
// 	while (str[i])
// 	{
// 		toggle_quotes(str[i], &in_single_quote, &in_double_quote);
// 		if (str[i] == '|' && !in_single_quote && !in_double_quote)
// 		{
// 			while (is_space(str[++i]))
// 				;
// 			if (str[i] == '|' && str[i - 1] != '|')
// 				return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// /*
// 	Location: validation.c
// 	This returns true if there are redirections in the command for execution
// */
// bool	check_redirections(char *str)
// {
// 	int	i;
// 	int	redir_char_len;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i = jump_quotation(str, i);
// 		redir_char_len = is_redirect(&str[i]);
// 		if (redir_char_len > 0)
// 		{
// 			if (!handle_redir_error(str, &i, redir_char_len))
// 				return (false);
// 			if (!str[i])
// 			{
// 				syntax_error_msg(REDIR_ERROR);
// 				return (false);
// 			}
// 			continue ;
// 		}
// 		if (str[i])
// 			i++;
// 	}
// 	return (true);
// }
