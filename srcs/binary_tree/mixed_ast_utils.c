#include "minishell.h"

void	populate_args(t_list **curr, char **args, int i)
{
	int	count;

	count = 0;
	if (i > 0)
		count = i;
	while ((*curr) && ((t_token *)(*curr)->content)->type == WORD)
	{
		args[count] = ft_strdup(((t_token *)(*curr)->content)->value);
		count++;
		next_token(curr);
	}
	args[count] = NULL;
}

// bool	is_valid_fd(t_list *curr)
// {
// 	int		i;
// 	t_token	*token;
// 	t_token	*next_token;

// 	if (!curr || !curr->next)
// 		return (false);
// 	token = (t_token *)curr->content;
// 	next_token = (t_token *)curr->next->content;
// 	if (!token || !next_token)
// 		return (false);
// 	i = -1;
// 	while (token->value[++i])
// 	{
// 		if (!ft_isdigit(token->value[i]))
// 			return (false);
// 	}
// 	if (token->type == WORD && ft_atoi(token->value) >= 0
// 		&& ft_atoi(token->value) <= 9)
// 	{
// 		if (next_token->type == INFILE || next_token->type == OUTFILE
// 			|| next_token->type == APPEND || next_token->type == HEREDOC)
// 			return (true);
// 	}
// 	return (false);
// }

void	copy_and_populate(char **av, t_list **curr, char **args)
{
	int	i;

	i = 0;
	while (av[i])
	{
		args[i] = ft_strdup(av[i]);
		i++;
	}
	args[i] = NULL;
	populate_args(curr, args, i);
	i = -1;
	while (av[++i])
		free(av[i]);
	free(av);
}

// t_in_out	*make_content(t_shell *shell, t_list **curr)
// {
// 	t_in_out	*content;

// 	content = malloc(sizeof(t_in_out));
// 	if (!content)
// 		exit_failure(shell, "make_content");
// 	content->name = ft_strdup(((t_token *)(*curr)->content)->value);
// 	content->fd_heredoc = ft_atoi(((t_token *)(*curr)->content)->value);
// 	next_token(curr);
// 	return (content);
// }
