#include "minishell.h"

bool	in_quotes(char *input, int i)
{
	if (input[i] == '"')
		return (true);
	return (false);
}

bool	is_meta(char *str, int i)
{
	int	j;
	char	*metachars;

	metachars = "<|>();&";
	j = 0;
	if (!str || i < 0)
		return (false);
	while (metachars[j] && str[i])
	{
		if (str[i] && str[i] == metachars[j])
			return (true);
		j++;
	}
	return (false);
}

int	set_append(t_shell *sh, t_token *nw_tkn, char *input, int i)
{
	nw_tkn->value = ft_strndup(&input[i], 2);
	if (!nw_tkn->value)
		exit_failure(sh, "handle_redirection_1");
	nw_tkn->type = APPEND;
	return (i + 2);
}

int	set_simple(t_shell *sh, t_token *nw_tkn, char *input, int i)
{
	nw_tkn->value = ft_strndup(&input[i], 1);
	if (!nw_tkn->value)
		exit_failure(sh, "handle_redirection_1");
	if (input[i] == '<')
		nw_tkn->type = INFILE;
	else
		nw_tkn->type = OUTFILE;
	return (i + 1);
}

bool	is_expandable(char *token)
{
	int	i;
	bool in_quotes;

	i = 0;
	in_quotes = false;
	while (is_space(token[i]))
		i++;
	if (token[i] == '\0')
		return (false);
	while (token[i])
	{
		if (is_quote(token[i]))
		{
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		if (token[i] == '$' && (token[i + 1] == '?' || ft_isalnum(token[i + 1])))
			return (true);
		if (!in_quotes && (is_space(token[i]) || is_meta(token, i)))
			return (false);
		i++;
	}
	return (false);
}
