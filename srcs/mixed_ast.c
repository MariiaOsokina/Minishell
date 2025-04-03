#include "minishell.h"

t_list	*next_token(t_list **current)
{
	if (current && *current)
		*current = (*current)->next;
	if (*current)
		printf("Current token is %s\n",
			((t_token *)(*current)->content)->value);
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

void	*parse_factor(t_shell *shell, t_list **curr)
{
	void	*node;

	if (!(*curr) || !(*curr)->content)
		return (NULL);
	if (*curr)
		printf("Parse fact cur token: %s\n",
			((t_token *)(*curr)->content)->value);
	if (((t_token *)(*curr)->content)->type == PARENTHESIS)
	{
		next_token(curr);
		node = parse_expression(shell, curr);
		past_parenthesis(curr);
		return (node);
	}
	node = create_exec_node(shell, curr);
	return (node);
}

void	*parse_term(t_shell *shell, t_list **curr)
{
	void	*left;
	t_pipe	*node;

	left = parse_factor(shell, curr);
	if (!left)
		return (NULL);
	if (*curr)
		printf("Current token in parse_term is %s\n",
			((t_token *)(*curr)->content)->value);
	while (*curr && (((t_token *)(*curr)->content)->type == PIPE))
	{
		node = malloc(sizeof(t_pipe));
		if (!node)
			return (NULL);
		node->type.type = N_PIPE;
		node->left = left;
		next_token(curr);
		node->right = parse_factor(shell, curr);
		if (!node->right)
		{
			printf("Right operand of PIPE is NULL\n");
			free_ast_node(node);
			return (NULL);
		}
		left = node;
	}
	printf("Returning left\n");
	return (left);
}

void	*parse_expression(t_shell *shell, t_list **curr)
{
	void	*left;
	t_op	*node;

	left = parse_term(shell, curr);
	if (*curr)
		printf("Current token in parse expression is %s\n", ((t_token *)(*curr)->content)->value);
	while (*curr && ((((t_token *)(*curr)->content)->type == OR)
			|| (((t_token *)(*curr)->content)->type == AND_IF)))
	{
		node = malloc(sizeof(t_op));
		if (!node)
			return (NULL);
		node->type.type = (((t_token *)(*curr)->content)->type == OR) ? N_OR : N_ANDIF;
		node->left = left;
		next_token(curr);
		printf("parsing right\n");
		node->right = parse_term(shell, curr);
		if (!node->right) // If parsing the right operand fails
		{
			printf("Right operand of %s is NULL\n", (node->type.type == N_ANDIF) ? "AND_IF" : "OR");
			free_ast_node(node);
			return (NULL); // Return NULL if the right operand is invalid
		}
		left = node;
	}
	return (left);
}

void	*build_ast(t_shell *shell)
{
	return (parse_expression(shell, &shell->token_lst));
}
