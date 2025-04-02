#include "minishell.h"

/*build_tree.c*/
void	*create_exec(t_shell *shell, t_list *token_lst)
{
	t_exec	*node;
	t_list	*current;

	printf("Called create_exec\n");
	if (!token_lst)
		return (NULL);
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		exit_failure(shell, "create_exec");
	node->type.type = N_EXEC;
	// node->infiles = NULL;
	node->command = NULL;
	node->av = NULL;
	// node->outfiles = NULL;
	node->in_out_list = NULL; //MO: added
	// get_infiles(shell, token_lst, &node->infiles);
	// get_outfiles(shell, token_lst, &node->outfiles);
	get_in_out_files(shell, token_lst, &node->in_out_list); //MO: added
	current = get_name(token_lst);
	if (current)
	{
		node->command = ((t_token *)current->content)->value;
		node->av = get_argv(shell, token_lst);
		if (ft_strcmp(node->av[0], "ls") == 0 || ft_strcmp(node->av[0], \
				"grep") == 0)
			node->av = get_colors(shell, node->av);
	}
	printf("created exec.\n");
	return (node);
}

/*build_tree.c*/
t_list	*get_name(t_list *tkn_lst)
{
	t_list	*word;

	word = NULL;
	while (tkn_lst && (((t_token *)tkn_lst->content)->type != PIPE))
	{
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
				|| ((t_token *)tkn_lst->content)->type == HEREDOC))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == OUTFILE
				|| ((t_token *)tkn_lst->content)->type == APPEND))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == WORD
				|| ((t_token *)tkn_lst->content)->state != EXPAND))
			return (tkn_lst);
		tkn_lst = tkn_lst->next;
		if (tkn_lst && ((t_token *)tkn_lst->content)->type == AND_IF)
			break ;
	}
	return (word);
}

/*build_tree.c*/
void	*create_pipe(t_shell *shell, void *left, void *right)
{
	t_pipe	*node;
	printf("called pipe\n");
	node = (t_pipe *)malloc(sizeof(t_pipe));
	if (!node)
		exit_failure(shell, "create_exec");
	node->type.type = N_PIPE;
	node->left = left;
	node->right = right;
	return (node);
}

/*build_tree.c*/
void	*insert_node(t_shell *shell, void *node, t_list *token_lst)
{
	t_list	*new;
	t_pipe	*pipe;

	printf("called insert node\n");
	if (!node)
		return (create_exec(shell, token_lst));
	if (is_parenthesis(token_lst->next))
	{
		new = NULL;
		new = new_sublist(token_lst->next);
		pipe = create_pipe(shell, node, build_ltree(shell, new));
		clean_sublist(new);
	}
	else
		pipe = create_pipe(shell, node, create_exec(shell, token_lst->next));
	return (pipe);
}

/*
	build_tree.c
	This function traverses the token list
	checks for most important nodes (pipes and and_if nodes) to add to the root.
	It dsipalces the previous root for the new root.
*/
void	*build_tree(t_shell *shell, t_list *token_lst)
{
	t_list	*tmp;
	void	*root;

	tmp = token_lst;
	root = NULL;
	while (check_token(tmp))
	{
		root = insert_node(shell, root, tmp);
		if (((t_token *)tmp->content)->type != PIPE)
			tmp = skip_if(tmp);
		else
			tmp = skip_else(tmp);
	}
	return (root);
}
