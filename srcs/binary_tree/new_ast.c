#include "minishell.h"

/*Token NAV*/

t_list	*next_token(t_list **current)
{
	if (current && *current)
		*current = (*current)->next;
	if (*current)
		printf("Current token is %s\n", ((t_token *)(*current)->content)->value);
	return (*current);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->right)
		free_ast(node->right);
	if (node->left)
		free_ast(node->left);
	free(node);
}

int	is_operator(t_list *token)
{
	if (!token || !token->content)
		return (0);
	return (((t_token *)token->content)->type == PIPE
		|| ((t_token *)token->content)->type == AND_IF
		|| ((t_token *)token->content)->type == OR);
}

void	past_parenthesis(t_list **curr)
{
	while (*curr && ((t_token *)(*curr)->content)->type == PARENTHESIS)
		next_token(curr);
}

t_ast	*create_redirection_node(t_ast *cmd, t_token *token)
{
	t_ast	*node;

	if (cmd)
		printf("Current token is %s\n", (cmd->cmd));
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = cmd;
	node->right = NULL;
	node->cmd = NULL;
	if (token->type == INFILE)
		node->type = N_INF;
	else if (token->type == OUTFILE)
		node->type = N_OUTF;
	else if (token->type == HEREDOC)
		node->type = N_HEREDOC;
	else if (token->type == APPEND)
		node->type = N_APPEND;
	return (node);
}

t_ast	*manage_redirection(t_list **curr, t_ast *cmd)
{
	t_ast	*node;

	if (*curr)
		printf("Current token is %s\n", ((t_token *)(*curr)->content)->value);
	node = create_redirection_node(cmd, (t_token *)(*curr)->content);
	if (!node)
		return (NULL);
	next_token(curr);
	if (!(*curr) || ((t_token *)(*curr)->content)->type != WORD)
	{
		printf("Error: Missing file for redirection.\n");
		free_ast(node);
		return (NULL);
	}
	node->right = malloc(sizeof(t_ast));
	if (!node->right)
	{
		free_ast(node);
		return (NULL);
	}
	if (*curr)
		printf("Current token is %s\n", ((t_token *)(*curr)->content)->value);
	node->right->cmd = ft_strdup(((t_token *)(*curr)->content)->value);
	node->right->type = N_EXEC;
	node->right->left = NULL;
	node->right->right = NULL;
	next_token(curr);
	return (node);
}

t_ast	*parse_redirection(t_list **curr, t_ast *cmd)
{
	t_ast	*redir_node;
	t_ast	*last_redir;
	t_token	*token;

	last_redir = NULL;
	if (!(*curr) || !(*curr)->content)
	{
		cmd->right = NULL;
		return (cmd);
	}
	if (cmd)
		printf("Current token is %s\n", ((cmd)->cmd));
	token = (t_token *)(*curr)->content;
	while (*curr && (token->type == INFILE || token->type == OUTFILE
			|| token->type == HEREDOC || token->type == APPEND))
	{
		redir_node = manage_redirection(curr, cmd);
		if (!redir_node)
			return (NULL);
		if (last_redir)
			last_redir->right = redir_node;
		else
			cmd = redir_node;
		last_redir = redir_node;
	}
	return (cmd);
}

t_ast	*parse_factor(t_list **curr, t_shell *shell)
{
	t_ast	*node;
	char	**args;

	if (!(*curr) || !(*curr)->content)
		return (NULL);
	printf("Current token is %s\n", ((t_token *)(*curr)->content)->value);
	if (((t_token *)(*curr)->content)->type == PARENTHESIS)
	{
		next_token(curr);
		node = parse_expression(curr, shell);
		past_parenthesis(curr);
		return (parse_redirection(curr, node));
	}
	// if (((t_token *)(*curr)->content)->type == WORD)
	// {
	// 	node = malloc(sizeof(t_ast));
	// 	if (!node)
	// 		return (NULL);
	// 	node->cmd = ft_strdup(((t_token *)(*curr)->content)->value);
	// 	node->type = N_EXEC;
	// 	node->right = NULL;
	// 	node->left = NULL;
	// 	next_token(curr);
	// 	return (parse_redirection(curr, node));
	// }
	// return (NULL);
	args = collect_args(curr);
	node = create_exec_node(args);
	return (parse_redirection(curr, node));
}

t_ast	*parse_term(t_list **curr, t_shell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_factor(curr, shell);
	if (!left)
		return (NULL);
	if (*curr)
		printf("Current token is %s\n", ((t_token *)(*curr)->content)->value);
	while (*curr && (((t_token *)(*curr)->content)->type == PIPE))
	{
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->type = N_PIPE;
		node->cmd = NULL;
		node->left = left;
		next_token(curr);
		node->right = parse_factor(curr, shell);
		if (!node->right)
		{
			printf("Error: Right operand of PIPE is NULL\n");
			free_ast(node);
			return (NULL);
		}
		left = node;
	}
	printf("Returning left\n");
	return (left);
}

t_ast	*parse_expression(t_list **curr, t_shell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_term(curr, shell);
	if (*curr)
		printf("Current token is %s\n", ((t_token *)(*curr)->content)->value);
	while (*curr && ((((t_token *)(*curr)->content)->type == OR)
			|| (((t_token *)(*curr)->content)->type == AND_IF)))
	{
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->type = (((t_token *)(*curr)->content)->type == OR) ? N_OR : N_ANDIF;
		node->cmd = NULL;
		node->left = left;
		next_token(curr);
		printf("parsing right\n");
		node->right = parse_term(curr, shell);
		if (!node->right) // If parsing the right operand fails
		{
			printf("Error: Right operand of %s is NULL\n",
				(node->type == N_ANDIF) ? "AND_IF" : "OR");
			free_ast(node);
			return (NULL); // Return NULL if the right operand is invalid
		}
		left = node;
	}
	return (left);
}

t_ast	*build_ast(t_shell *shell)
{
	return (parse_expression(&shell->token_lst, shell));
}

// void	print_ast(t_ast *node, int level)
// {
// 	// Base case: If node is NULL, return immediately.
// 	if (node == NULL)
// 		return ;
// 	// Print the right subtree first (for rightward indentation)
// 	if (node->right)
// 	{
// 		print_ast(node->right, level + 1);
// 		// Recursive call to print right subtree
// 	}
// 	else
// 	{
// 		// If the right child is NULL, print a warning (optional)
// 		// printf("Warning: Right child is NULL at level %d\n", level);
// 	}
// 	// Indentation based on level in the tree
// 	for (int i = 0; i < level; i++)
// 	{
// 		printf("   "); // Indent to the right
// 	}
// 	// Print the current node's type or command
// 	if (node->type == N_ANDIF)
// 	{
// 		printf("[&&]\n");
// 	}
// 	else if (node->type == N_OR)
// 	{
// 		printf("[||]\n");
// 	}
// 	else if (node->type == N_PIPE)
// 	{
// 		printf("[PIPE `|`]\n");
// 	}
// 	else if (node->type == N_EXEC)
// 	{
// 		// print_bst_exec((t_exec *)node, level + 1);
// 		printf("[EXEC] %s\n", (char *)node->cmd);
// 		// Print execution node details
// 	}
// 	else if (node->type == N_HEREDOC)

// 	// Print the left subtree recursively
// 	if (node->left)
// 	{
// 		print_ast(node->left, level + 1);
// 		// Recursive call to print left subtree
// 	}
// 	else
// 	{
// 		// If the left child is NULL, print a warning (optional)
// 		// printf("Warning: Left child is NULL at level %d\n", level);
// 	}
// }

void	print_ast(t_ast *node, int level)
{
	if (!node)
		return ;
	// Print right subtree first (for better visualization)
	print_ast(node->right, level + 1);
	// Indentation for tree structure
	for (int i = 0; i < level; i++)
		printf(" ");
	// Print node type
	if (node->type == N_PIPE)
		printf("[N_PIPE]\n");
	else if (node->type == N_EXEC)
		printf("[N_EXEC] (%s)\n", node->cmd ? node->cmd : "NULL");
	else if (node->type == N_ANDIF)
		printf("[N_ANDIF]\n");
	else if (node->type == N_OR)
		printf("[N_OR]\n");
	else if (node->type == N_HEREDOC)
		printf("[N_HEREDOC]\n");
	else if (node->type == N_INF)
		printf("[N_INF]\n");
	else if (node->type == N_OUTF)
		printf("[N_REDIRECT_OUT]\n");
	else if (node->type == N_APPEND)
		printf("[N_APPEND]\n");
	// Print left subtree
	print_ast(node->left, level + 1);
}
