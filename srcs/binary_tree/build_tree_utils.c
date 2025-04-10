#include "minishell.h"

/*build_tree_utils.c*/
t_list	*get_in_out_files(t_shell *shell, t_list *tkn_lst, t_list **in_out_list) //MO: added
{
	t_in_out	*content;

	// printf("Got here-7.0\n");
	// while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE) 
	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE
		&&  ((t_token *)tkn_lst->content)->type != AND_IF
		&& ((t_token *)tkn_lst->content)->type != OR)
	{
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
				|| ((t_token *)tkn_lst->content)->type == HEREDOC
				|| ((t_token *)tkn_lst->content)->type == OUTFILE
				|| ((t_token *)tkn_lst->content)->type == APPEND))
		{
			content = ft_calloc(sizeof(t_in_out), 1);
			if (!content)
				exit_failure(shell, "get_in_out_files");
			if (((t_token *)tkn_lst->content)->type == INFILE)
				content->type = INF;
			else if (((t_token *)tkn_lst->content)->type == HEREDOC)
				content->type = HERE;
			else if (((t_token *)tkn_lst->content)->type == APPEND)
				content->type = APP;
			else
				content->type = ADD;
			if (content->type == HERE)
				content->eof = ft_strdup(((t_token *)tkn_lst->next->content)->value);
			else
			{
				content->name = ft_strdup(((t_token *)tkn_lst->next->content)->value);
				// content->expanded_name[0] = ft_strdup(((t_token *)tkn_lst->next->content)->value); // MO: add to free
			}
			ft_lstadd_back(in_out_list, ft_lstnew(content));
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		// printf("Got here-7.1\n");
		tkn_lst = tkn_lst->next;
		if (tkn_lst == NULL || !check_token(tkn_lst))
			break ;
	}
	// printf("Got here-7.2\n");
	return (tkn_lst);
}


// // /*build_tree_utils.c*/
// t_list	*get_infiles(t_shell *shell, t_list *tkn_lst, t_list **infs)
// {
// 	t_inf	*content;

// 	printf("Got here-7.0\n");
// 	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
// 	{
// 		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
// 				|| ((t_token *)tkn_lst->content)->type == HEREDOC))
// 		{
// 			content = ft_calloc(sizeof(t_inf), 1);
// 			if (!content)
// 				exit_failure(shell, "get_infiles");
// 			if (((t_token *)tkn_lst->content)->type == INFILE)
// 				content->type = INF;
// 			else
// 				content->type = HERE;
// 			content->eof = ft_strdup(((t_token *)tkn_lst->next->content)->value);
// 			ft_lstadd_back(infs, ft_lstnew(content));
// 			tkn_lst = tkn_lst->next->next;
// 			continue ;
// 		}
// 		printf("Got here-7.1\n");
// 		tkn_lst = tkn_lst->next;
// 		if (tkn_lst == NULL || !check_token(tkn_lst))
// 			break ;
// 	}
// 	printf("Got here-7.2\n");
// 	return (tkn_lst);
// }

// /*build_tree_utils.c*/
// t_list	*get_outfiles(t_shell *shell, t_list *tkn_lst, t_list **outfs)
// {
// 	t_outf	*content;

// 	printf("Got here 71.0\n");
// 	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
// 	{
// 		if (tkn_lst && (((t_token *)tkn_lst->content)->type == OUTFILE
// 				|| ((t_token *)tkn_lst->content)->type == APPEND))
// 		{
// 			content = ft_calloc(1, sizeof(t_outf));
// 			if (!content)
// 				exit_failure(shell, "get_outfiles");
// 			if (((t_token *)tkn_lst->content)->type == APPEND)
// 				content->type = APP;
// 			else
// 				content->type = ADD;
// 			content->name = ft_strdup(((t_token *)tkn_lst->next->content)->value);
// 			ft_lstadd_back(outfs, ft_lstnew(content));
// 			tkn_lst = tkn_lst->next->next;
// 			continue ;
// 		}
// 		tkn_lst = tkn_lst->next;
// 		if (tkn_lst == NULL || !check_token(tkn_lst))
// 			break ;
// 	}
// 	printf("Got here 71.1\n");
// 	return (tkn_lst);
// }

/*build_tree_utils.c*/
char	**get_argv(t_shell *shell, t_list *t_lst)
{
	int		i;
	int		ac;
	char	**av;

	i = 0;
	ac = 0;
	ac = count_args(t_lst);
	av = ft_calloc(sizeof(char *), ac + 1);
	if (!av)
		exit_failure(shell, "get_argv");
	// printf("Got here 8.0\n");
	while (t_lst && ((t_token *)t_lst->content)->type != PIPE && i < ac)
	{
		// printf("Got here 8.1\n");
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
	// printf("Got here 8.2\n");
	return (av[ac] = NULL, av);
}

/*build_tree_utils.c*/
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
