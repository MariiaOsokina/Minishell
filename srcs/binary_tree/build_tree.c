#include "minishell.h"

void	*parse_factor(t_shell *shell, t_list **curr, bool in_subshell)
{
	void	*node;
	t_token	*tmp;
	t_op	*subshell_node;

	if (!(*curr) || !(*curr)->content)
		return (NULL);
	tmp = (t_token *)(*curr)->content;
	if (tmp->type == PARENTHESIS && ft_strcmp(tmp->value, "(") == 0)
	{
		next_token(curr);
		node = parse_expression(shell, curr, true);
		if (!node)
			return (NULL);
		next_token(curr); // Can do parenthesis count later.
		if (!in_subshell)
		{
			subshell_node = malloc(sizeof(t_op));
			subshell_node->left = node;
			subshell_node->right = NULL;
			subshell_node->type.type = N_SUBSHELL;
			return (subshell_node);
		}
		return (node);
	}
	return (create_exec_node(shell, curr));
}

void	*parse_term(t_shell *shell, t_list **curr, bool in_subshell)
{
	void	*left;
	t_pipe	*node;

	left = parse_factor(shell, curr, in_subshell);
	if (!left)
		return (NULL);
	while (*curr && (((t_token *)(*curr)->content)->type == PIPE))
	{
		node = malloc(sizeof(t_pipe));
		if (!node)
			return (NULL);
		node->type.type = N_PIPE;
		node->left = left;
		next_token(curr);
		node->right = parse_factor(shell, curr, in_subshell);
		if (!node->right)
		{
			free_ast_node(node);
			return (NULL);
		}
		left = node;
	}
	return (left);
}

void	*parse_expression(t_shell *shell, t_list **curr, bool in_subshell)
{
	void	*left;
	t_op	*node;

	left = parse_term(shell, curr, in_subshell);
	while (*curr && ((((t_token *)(*curr)->content)->type == OR)
			|| (((t_token *)(*curr)->content)->type == AND_IF)))
	{
		node = malloc(sizeof(t_op));
		if (!node)
			return (NULL);
		node->type.type = (((t_token *)(*curr)->content)->type == OR) ? N_OR : N_ANDIF;
		node->left = left;
		next_token(curr);
		node->right = parse_term(shell, curr, in_subshell);
		if (!node->right) // If parsing the right operand fails
		{
			free_ast_node(node);
			return (NULL); // Return NULL if the right operand is invalid
		}
		left = node;
	}
	return (left);
}

void	*build_ast(t_shell *shell)
{
	return (parse_expression(shell, &shell->token_lst, false));
}
