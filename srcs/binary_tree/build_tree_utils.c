#include "minishell.h"

t_list	*next_token(t_list **current)
{
	if (current && *current)
		*current = (*current)->next;
	return (*current);
}

int	is_operator(t_list *token)
{
	if (!token || !token->content)
		return (0);
	return (((t_token *)token->content)->type == PIPE
		|| ((t_token *)token->content)->type == AND_IF
		|| ((t_token *)token->content)->type == OR);
}

int	is_redirection(t_list *token)
{
	if (!token || !token->content)
		return (0);
	return (((t_token *)token->content)->type == APPEND
		|| ((t_token *)token->content)->type == OUTFILE
		|| ((t_token *)token->content)->type == INFILE
		|| ((t_token *)token->content)->type == HEREDOC);
}

void	past_parenthesis(t_list **curr)
{
	while (*curr && ((t_token *)(*curr)->content)->type == PARENTHESIS)
		next_token(curr);
}

/*build_tree_utils.c*/
char	**get_colors(t_shell *shell, char **av)
{
	int		i;
	int		j;
	char	**colors;

	i = 0;
	j = 1;
	while (av[i])
		i++;
	colors = malloc(sizeof(char *) * (i + 2));
	if (!colors)
		exit_failure(shell, "get_colors");
	colors[0] = av[0];
	colors[1] = "--color=auto";
	while (j < i)
	{
		colors[j + 1] = av[j];
		j++;
	}
	colors[i + 1] = NULL;
	free(av);
	return (colors);
}
