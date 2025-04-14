#include "minishell.h"

char	**populate_args(t_list **curr, char **args)
{
	int	count;

	count = 0;
	while ((*curr) && ((t_token *)(*curr)->content)->type == WORD)
	{
		args[count] = ft_strdup(((t_token *)(*curr)->content)->value);
		count++;
		next_token(curr);
	}
	args[count] = NULL;
	return (args);
}

void	free_ast_node(void *node)
{
	if (!node)
		return ;
	if (((t_node *)node)->type == N_PIPE)
	{
		free_ast_node(((t_pipe *)node)->right);
		free_ast_node(((t_pipe *)node)->left);
	}
	else if ((((t_node *)node)->type == N_ANDIF
			|| (((t_node *)node)->type == N_OR)))
	{
		free_ast_node(((t_op *)node)->right);
		free_ast_node(((t_op *)node)->left);
	}
	free(node);
}

bool	is_valid_fd(t_list *curr)
{
	int	i;
	t_token	*token;
	t_token	*next_token;

	if (!curr || !curr->next)
		return (false);
	token = (t_token *)curr->content;
	next_token = (t_token *)curr->next->content;
	if (!token || !next_token)
		return (false);
	i = -1;
	while (token->value[++i])
	{
		if (!ft_isdigit(token->value[i]))
			return (false);
	}
	if (token->type == WORD && ft_atoi(token->value) >= 0
		&& ft_atoi(token->value) <= 9)
	{
		if (next_token->type == INFILE || next_token->type == OUTFILE
				|| next_token->type == APPEND || next_token->type == HEREDOC)
				return (true);
	}
	return (false);
}

char	**collect_args(t_list **curr)
{
	char	**args;
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = *curr;
	while (tmp && ((t_token *)(tmp->content))->type == WORD)
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	args = populate_args(curr, args);
	return (args);
}

t_in_out	*redirection_content(t_shell *shell, t_list **curr)
{
	t_token		*tmp;
	t_in_out	*content;

	content = malloc(sizeof(t_in_out));
	if (!content)
		exit_failure(shell, "collect_io");
	tmp = (t_token *)(*curr)->content;
	if (tmp->type == INFILE)
		content->type = INF;
	else if (tmp->type == HEREDOC)
		content->type = HERE;
	else if (tmp->pos == OUTFILE)
		content->type = ADD;
	else if (tmp->type == APPEND)
		content->type = APP;
	if (content->type == HERE)
	{
		content->eof = ft_strdup(((t_token *)(*curr)->next->content)->value);
		content->name = ft_strdup(((t_token *)(*curr)->next->content)->value);
	}
	else
		content->name = ft_strdup(((t_token *)(*curr)->next->content)->value);
	return (content);
}

t_in_out	*make_content(t_shell *shell, t_list **curr)
{
	t_in_out	*content;

	content = malloc(sizeof(t_in_out));
	if (!content)
		exit_failure(shell, "make_content");
	content->name = ft_strdup(((t_token *)(*curr)->content)->value);
	content->fd_heredoc = ft_atoi(((t_token *)(*curr)->content)->value);
	// if (*curr)
	next_token(curr);
	return (content);
}

void	collect_io(t_shell *shell, t_list **curr, t_list **i_ofiles)
{
	t_in_out	*content;

	if (*curr && is_redirection(*curr))
	{
		while (*curr && !is_operator(*curr) )
		{
			if (is_valid_fd(*curr))
			{
				content = make_content(shell, curr);
				ft_lstadd_back(i_ofiles, ft_lstnew(content));
			}
			else if (is_redirection(*curr))
			{
				// printf("Current token in collect i_o %s\n",
				// 	((t_token *)(*curr)->content)->value);
				content = redirection_content(shell, curr);
				ft_lstadd_back(i_ofiles, ft_lstnew(content));
				if (!((*curr) = ((*curr)->next)->next))
					break ;
				printf("The value of curr in collect_io %s\n", ((t_token *)(*curr)->content)->value);
			}
			else
				break ;
		}
	}
	return ;
}

void	*create_exec_node(t_shell *shell, t_list **curr)
{
	t_exec	*node;

	if (!(*curr))
		return (NULL);
	node = malloc(sizeof(t_exec));
	if (!node)
		exit_failure(shell, "create_exec");
	node->type.type = N_EXEC;
	node->i_ofiles = NULL;
	node->av = collect_args(curr);
	collect_io(shell, curr, &node->i_ofiles);
	if (node->i_ofiles)
	{
		if (((t_token *)(*curr)->content)->type == WORD)
		{
			node->command = ft_strdup(((t_token *)(*curr)->content)->value);
			// next_token(curr);
			node->av = collect_args(curr); // Was not here initially
			if (is_redirection(*curr))
				collect_io(shell, curr, &node->i_ofiles);
		}
	}
	// Needs to be freed.
	if (node->av)
	{
		node->command = ft_strdup(node->av[0]); // Needs to be freed;
		if (ft_strcmp(node->av[0], "ls") == 0 || ft_strcmp(node->av[0],
				"grep") == 0)
			node->av = get_colors(shell, node->av);
	}
	printf("created exec\n");
	return (node);
}
