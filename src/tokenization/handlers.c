#include "minishell.h"

int	handle_or(t_shell *shell, char *input, int i)
{
	t_token	*new_token;
	char	*str;

	str = ft_strdup("||");
	i += 2;
	if (!str)
		exit_failure(shell, "handle_or");
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->value = str;
	new_token->type = OR;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	while (is_space(input[i]))
		i++;
	return (i);
}

int	handle_andif(t_shell *shell, char *input, int i)
{
	char	*str;
	t_token	*new_token;

	str = ft_strdup("&&");
	i += 2;
	if (!str)
		exit_failure(shell, "handle_expansion");
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->value = str;
	new_token->type = AND_IF;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	while (is_space(input[i]))
		i++;
	return (i);
}

int	hndl_nonquoted_str(t_shell *shell, char **str, char *input, int i)
{
	int		start;
	char	*join;
	char	*tmp;

	start = i;
	while (input[i] && !is_quote(input[i]) && !is_space(input[i])
		&& !is_meta(input, i))
		i++;
	join = ft_substr(input, start, i - start);
	if (!join)
		exit_failure(shell, "handle_nonquoted_str");
	tmp = *str;
	*str = ft_strjoin(*str, join);
	free(tmp);
	free(join);
	if (!str)
		exit_failure(shell, "handle_non_quoted_str_a");
	return (i);
}

int	hndl_quoted_str(t_shell *shell, char **str, char *input, int i)
{
	int		start;
	char	*tmp;
	char	*join;
	char	quote;

	quote = input[i];
	start = i++;
	i = check_escapes(input, start, i, quote);
	if (i == -1)
		exit_failure(shell, "handle_quoted_str_unclosed_detected");
	join = ft_substr(input, start + 1, i - start - 1);
	// extracting without the quotes.
	if (!join)
		exit_failure(shell, "handle_quoted_str"); // TODO: Ensure exit code of the prev comnd is set in the shell.
	tmp = *str;
	*str = ft_strjoin(*str, join);
	free(tmp);
	free(join);
	if (!*str)
		exit_failure(shell, "handle_quoted_str_a");
	return (++i);
}

int	handle_quotes(t_shell *shell, char *input, int i)
{
	char		*str;
	t_token		*new_token;
	const char	quote = input[i];

	new_token = ft_calloc(1, sizeof(t_token));
	str = ft_strdup("");
	if (!new_token || !str)
		exit_failure(shell, "handle_quotes");
	while (input[i] && !is_space(input[i]) && !is_meta(input, i))
		i = join_strs(shell, &str, input, i);
	new_token->value = str;
	if (!new_token->value)
		exit_failure(shell, "handle_quotes_a");
	new_token->type = WORD;
	if (quote == '"')
		new_token->state = IN_DQUOTES;
	else if (quote == '\'')
		new_token->state = IN_SQUOTES;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	while (is_space(input[i]))
		i++;
	return (i);
}
