#include "minishell.h"

t_list	*get_infiles(t_shell *shell, t_list *tkn_lst, t_list **infs)
{
	t_inf	*content;

	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
	{
		t_inf	*content;

		while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
		{
			if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
					|| ((t_token *)tkn_lst->content)->type == HEREDOC))
			{
				content = ft_calloc(sizeof(t_inf), 1);
				if (!content)
					exit_failure(shell, "get_infiles");
				if (((t_token *)tkn_lst->content)->type == INFILE)
					content->type = INF;
				else
					content->type = HERE;
				content->eof = ft_strdup(((t_token *)
									tkn_lst->next->content)->value);
				ft_lstadd_back(infs, ft_lstnew(content));
				tkn_lst = tkn_lst->next->next;
				continue ;
			}
			tkn_lst = tkn_lst->next;
			if (!check_token(tkn_lst))
				break ;
		}
		return (tkn_lst);
	}
}

t_list	*get_outfiles(t_shell *shell, t_list *tkn_lst, t_list **outfs)
{
	t_outf	*content;

	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
	{
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == OUTFILE \
				|| ((t_token *)tkn_lst->content)->type == APPEND))
		{
			content = ft_calloc(1, sizeof(t_outf));
			if (!content)
				exit_failure(shell, "get_outfiles");
			if (((t_token *)tkn_lst->content)->type == APPEND)
				content->type = APP;
			else
				content->type = ADD;
			content->name = ft_strdup(((t_token *)
								tkn_lst->next->content)->value);
			ft_lstadd_back(outfs, ft_lstnew(content));
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		tkn_lst = tkn_lst->next;
		if (!check_token(tkn_lst))
			break ;
	}
	return (tkn_lst);
}

char	**get_argv(t_shell *shell, t_list *t_lst)
{
	int	i;
	int	ac;
	char	**av;

	i = 0;
	ac = 0;
	ac = count_args(t_lst);
	av = ft_calloc(sizeof(char *), ac + 1);
	if (!av)
		exit_failure(shell, "get_argv");
	while (t_lst && ((t_token *)t_lst->content)->type != PIPE && i < ac)
	{
		if (!check_token(t_lst))
			break ;
		if (t_lst && ((t_token *)t_lst->content)->type == WORD)
		{
			t_lst = check_word(&t_lst, av, &i);
			continue ;
		}
		if (!check_token(t_lst->next))
			break ;
		t_lst = t_lst->next->next;
	}
	return (av[ac] = NULL, av);
}

int	count_args(t_list *tkn_lst)
{
	int	args;

	args = 0;
	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
	{
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
				|| ((t_token *)tkn_lst->content)->type == HEREDOC))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		tkn_lst = check_w_args(tkn_lst, &args);
		if (!check_token(tkn_lst))
			break ;
	}
	return (args);
}

char	**get_colors(t_shell *shell, char **av)
{
	int	i;
	int	j;
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
