#include "minishell.h"

/*create_token_lst.c*/
int	set_hered(t_shell *sh, t_token *nw_tkn, char *input, int i)
{
	nw_tkn->value = ft_strndup(&input[i], 2);
	if (!nw_tkn->value)
		exit_failure(sh, "handle_redir_2");
	nw_tkn->type = HEREDOC;
	return (i + 2);
}

/*create_token_lst.c*/
int	handle_redirection(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_redir");
	if (input[i] == '>' && input[i + 1] == '>')
		i = set_append(shell, new_token, input, i);
	else if (input[i] == '<' && input[i + 1] == '<')
		i = set_hered(shell, new_token, input, i);
	else
		i = set_simple(shell, new_token, input, i);
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	while (is_space(input[i]))
		i++;
	return (i);
}

/*create_token_lst.c*/
int	handle_pipe(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_pipe");
	new_token->value = ft_strndup(&input[i], 1);
	new_token->type = PIPE;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	i++;
	while (is_space(input[i]))
		i++;
	return (i);
}

/*create_token_lst.c*/
int	handle_word_token(t_shell *shell, char *input, int i)
{
	char	*str;
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	str = ft_strdup("");
	if (!new_token || !str)
		exit_failure(shell, "handle_word_token");
	while (input[i] && !is_space(input[i]) && !is_meta(input, i))
		i = join_strs(shell, &str, input, i);
	new_token->value = str;
	if (!new_token->value)
		exit_failure(shell, "handle_word_token_a");
	new_token->type = WORD;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	while (is_space(input[i]))
		i++;
	return (i);
}

/*create_token_lst.c*/
void	tokenize_input(t_shell *shell, char *input)
{
	int	i;
	int	prev_i;

	i = 0;
	while (input[i])
	{
		prev_i = i;
		if (input[i] == '|' && input[i + 1] == '|')
			i = handle_or(shell, input, i);
		else if (input[i] == '|')
			i = handle_pipe(shell, input, i);
		else if (input[i] == '(' || input[i] == ')')
			i = handle_parenthesis(shell, input, i);
		else if (input[i] == '&' && input[i + 1] == '&')
			i = handle_andif(shell, input, i);
		else if (input[i] == '>' || input[i] == '<')
			i = handle_redirection(shell, input, i);
		else
			i = handle_word_token(shell, input, i);
		if (i == prev_i)
			i++;
		set_token_position(shell->token_lst);
	}
}
