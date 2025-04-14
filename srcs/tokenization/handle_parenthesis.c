#include "minishell.h"

int	skip_spaces(char *input, int i)
{
	i++;
	while (is_space(input[i]))
		i++;
	return (i);
}

bool	validate_subs(char *subs)
{
	int		i;

	i = 0;
	if (!subs)
		return (false);
	while (subs[i])
	{
		if (subs[i] == '|' || subs[i] == '&')
			return (true);
		i++;
	}
	return (false);
}

int	handle_closing(t_shell *shell, char *input, int i, bool valid)
{
	char	*str;
	t_token	*new_token;

	if (input[i] == ')' && valid)
	{
		str = ft_strdup(")");
		i++;
		if (!str)
			exit_failure(shell, "handle_parenthesis");
		new_token = ft_calloc(1, sizeof(t_token));
		new_token->value = str;
		new_token->type = PARENTHESIS;
		new_token->state = GENERAL;
		ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
		while (is_space(input[i]))
			i++;
		return (i);
	}
	else
	{
		i = skip_spaces(input, i);
		return (i);
	}
	return (-1);
}

int	handle_opening(t_shell *shell, char *input, int i, bool valid)
{
	char	*str;
	t_token	*new_token;

	str = NULL;
	if (valid)
	{
		if (input[i] == '(')
			str = ft_substr(input, i, 1);
		if (!str)
			exit_failure(shell, "handle_parenthesis");
		i++;
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
		{
			free(str);
			exit_failure(shell, "handle_parenthesis_a");
		}
		new_token->value = str;
		new_token->type = PARENTHESIS;
		new_token->state = GENERAL;
		ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
		while (is_space(input[i]))
			i++;
		return (i);
	}
	return (-1);
}

int	handle_parenthesis(t_shell *shell, char *input, int i)
{
	int			start;
	char		*subs;
	static bool	valid = true;//was false

	if (input[i] == ')')
	{
		i = handle_closing(shell, input, i, valid);
		if (i != -1)
			return (i);
	}
	start = i;
	i = check_balance(input, i);
	subs = ft_substr(&input[start + 1], 0, i - start - 1);
	// valid = validate_subs(subs);'
	free(subs);
	i = handle_opening(shell, input, start, valid);
	if (i != -1)
		return (i);
	if (input[start] && input[start] == '(')
		start++;
	while (is_space(input[start]))
		start++;
	return (start);
}
