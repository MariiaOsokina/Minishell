#include "minishell.h"

/*build_ltree.c*/
// void	*create_subtree(t_shell *shell, t_list *token_lst)
// {
// 	void	*subtree;

// 	printf("create subtree was called\n");
// 	if (!token_lst)
// 		return (NULL);
// 	subtree = build_tree(shell, token_lst);
// 	if (!subtree)
// 		exit_failure(shell, "create_subtree");
// 	printf("subtree created\n");
// 	return (subtree);
// }

/*build_ltree.c*/
// void	*create_and(t_shell *shell, void *left, void *right)
// {
// 	t_andif	*node;

// 	node = malloc(sizeof(t_andif));
// 	if (!node)
// 		exit_failure(shell, "create_andif");
// 	node->type.type = N_ANDIF;
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }

// /*build_ltree.c*/
// void	*create_or(t_shell *shell, void *left, void *right)
// {
// 	t_or	*node;

// 	node = malloc(sizeof(t_or));
// 	if (!node)
// 		exit_failure(shell, "create_or");
// 	node->type.type = N_OR;
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }

/*build_ltree.c*/
// void	*insert_lnode(t_shell *shell, void *l_node, t_list *t_lst)
// {
// 	t_token	*token;

// 	printf("Got here-2\n");
// 	token = (t_token *)t_lst->content;

// 	if (token->type == PARENTHESIS)
// 		return (start_parenthesis(shell, t_lst, l_node));
// 	if (!l_node)
// 		return (create_subtree(shell, t_lst));
// 	if (token->type == AND_IF && !is_parenthesis(t_lst->next))
// 		l_node = create_and(shell, l_node, create_subtree(shell, t_lst->next));
// 	else if (token->type == AND_IF && is_parenthesis(t_lst->next))
// 		l_node = get_andif_subnode(shell, l_node, t_lst);
// 	else if (token->type == OR && !is_parenthesis(t_lst->next))
// 		l_node = create_or(shell, l_node, create_subtree(shell, t_lst->next));
// 	else if (token->type == OR && is_parenthesis(t_lst->next))
// 		l_node = get_or_subnode(shell, l_node, t_lst);
// 	else if (token->type == PIPE && is_parenthesis(t_lst->next))
// 		l_node = get_pipe_subnode(shell, l_node, t_lst);
// 	else if (token->type == PIPE && !is_parenthesis(t_lst->next))
// 		l_node = create_pipe(shell, l_node, create_exec(shell, t_lst->next));
// 	return (l_node);
// }

/*build_ltree.c*/
// void	*build_ltree(t_shell *shell, t_list *token_list)
// {
// 	t_list	*tmp;
// 	void	*lroot;

// 	tmp = token_list;
// 	lroot = NULL;
// 	while (tmp)
// 	{
// 		printf("processing %s\n", ((t_token *)tmp->content)->value);
// 		lroot = insert_lnode(shell, lroot, tmp);
// 		if (check_token(tmp) && !is_parenthesis(tmp))
// 			tmp = get_new_token(tmp);
// 		else
// 		{
// 			if (is_parenthesis(tmp))
// 				tmp = jump_parenthesis(tmp);
// 			else
// 			{
// 				tmp = tmp->next;
// 				while (check_token(tmp) && !is_parenthesis(tmp))
// 					tmp = tmp->next;
// 			}
// 		}
// 	}
// 	return (lroot);
// }
