#include "minishell.h"

char	**populate_args(t_list **curr, char **args, int i)
{
	int	count;

	if (i > 0)
		count = i;
	else
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
	int		i;
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

int	get_av_len(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	**copy_and_populate(char **av, t_list **curr, char **args)
{
	int		i;
	char	**copied_args;

	i = 0;
	while (av[i])
	{
		args[i] = ft_strdup(av[i]);
		i++;
	}
	copied_args = populate_args(curr, args, i);
	i = -1;
	while (av[++i])
		free(av[i]);
	free(av);
	return (copied_args);
}

char	**collect_args(char **argv, t_list **curr)
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
	if (argv)
		args = malloc(sizeof(char *) * (count + get_av_len(argv) + 1));
	else
		args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	if (argv)
		args = copy_and_populate(argv, curr, args);
	else
		args = populate_args(curr, args, 0);
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
		while (*curr && !is_operator(*curr))
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
				printf("The value of curr in collect_io %s\n",
					((t_token *)(*curr)->content)->value);
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
	node->av = collect_args(node->av, curr);
	collect_io(shell, curr, &node->i_ofiles);
	if (node->av) // Was second
	{
		node->command = ft_strdup(node->av[0]); // Needs to be freed;
		if (ft_strcmp(node->av[0], "ls") == 0 || ft_strcmp(node->av[0],
				"grep") == 0)
			node->av = get_colors(shell, node->av);
	}
	if (node->i_ofiles) // was first
	{
		while ((*curr) && ((t_token *)(*curr)->content)->type == WORD
			&& !is_operator(*curr))
		{
			// node->command = ft_strdup(((t_token *)(*curr)->content)->value);
			// next_token(curr);
			node->av = collect_args(node->av, curr); // Was not here initially
			node->command = ft_strdup(node->av[0]);
			if (is_redirection(*curr))
				collect_io(shell, curr, &node->i_ofiles);
		}
	}
	// Needs to be freed.
	printf("created exec\n");
	return (node);
}
