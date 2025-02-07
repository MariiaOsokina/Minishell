# include "minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_redirect(char *c)
{
	if (c[0] == '>')
	{
		if (c[1] == '>')
			return (2);
		return (1);
	}
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (2);
		return (1);
	}
	return (0);
}

/*The function toggle_quote is being used to track texts in single and double quotes*/
void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote; //Toggles single quote if not in double quote;
	else if (c == '\"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote; //Toggle double quote if not in single quote;
}

/*Loops through or skips texts in single or double quotes*/
/* This also ensure redirections in quotes are not processed*/
int	jump_quotation(char *str, int i)
{
	if (str[i] && is_quote(str[i]))
	{
		i++;
		while (str[i] && !is_quote(str[i]))
			i++;
		if (str[i])
			i++;
	}
	return (i);
}

/*
	This function is handling different
	edge cases of wrong syntax combinations
*/
bool	handle_redir_error(char *str, int *i, int redir_len)
{
	char	*error_msg;

	if (str[*i + 1] == '|')
	{
		syntax_error_msg("near unexpected token `|'");
		return (false);
	}
	*i += redir_len;
	while (str[*i] && is_space(str[*i]))
		(*i)++;
	if (is_redirect(&str[*i]) || is_meta(str, *i))
	{
		if (str[*i] == '>' && str[*i + 1] == '>')
			error_msg = "near unexpected token `>>'";
		else if (str[*i] == '<' && str[*i + 1] == '<')
			error_msg = "near unexpected token `<<'";
		else if (str[*i] == '>')
			error_msg = "near unexpected token `>'";
		else
			error_msg = "near unexpected token `<'";
		syntax_error_msg(error_msg);
		return (false);
	}
	return (true);
}
