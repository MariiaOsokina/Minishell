#include "minishell.h"

char	**collect_args(char **argv, t_list **curr)
{
	char	**args;
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = *curr;
	args = NULL;
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
				content = redirection_content(shell, curr);
				ft_lstadd_back(i_ofiles, ft_lstnew(content));
				if (!((*curr) = ((*curr)->next)->next))
					break ;
			}
			else
				break ;
		}
	}
	return ;
}

void	repopulate_args(t_shell *shell, t_list **curr, t_exec *node)
{
	while ((*curr) && ((t_token *)(*curr)->content)->type == WORD
		&& !is_operator(*curr))
	{
		node->av = collect_args(node->av, curr); // Was not here initially
		node->command = ft_strdup(node->av[0]);
		if (is_redirection(*curr))
			collect_io(shell, curr, &node->i_ofiles);
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
		repopulate_args(shell, curr, node);
	return (node);
}
