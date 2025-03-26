#include "minishell.h"

int	check_token(t_list *node)
{
	printf("Got here-4.5\n");
	// printf("%s\n", ((t_token *)node->content)->value);
	return (node && (((t_token *)node->content)->type != AND_IF
			&& ((t_token *)node->content)->type != OR));
}

void	*ltree_print(void *root, int space)
{
	int		spacing;
	t_node	*node;

	spacing = 5;
	space += spacing;
	if (!root)
		return (NULL);
	node = (t_node *)root;
	if (node->type == N_ANDIF)
	{
		ltree_print(((t_andif *)root)->right, space);
		printf("%*s -> [&&]\n", space, "");
		ltree_print(((t_andif *)root)->left, space);
	}
	else if (node->type == N_OR)
	{
		ltree_print(((t_or *)root)->right, space);
		printf("%*s -> [||]\n", space, "");
		ltree_print(((t_or *)root)->left, space);
	}
	else if (node->type == N_PIPE)
		print_bst((t_pipe *)root, space + spacing);
	else if (node->type == N_EXEC)
		print_bst_exec((t_exec *)root, space + spacing);
	return (NULL);
}

void	ltree_free(void *root)
{
	t_node	*node;

	if (!root)
		return ;
	node = (t_node *)root;
	if (node->type == N_ANDIF)
	{
		ltree_free(((t_andif *)node)->left);
		ltree_free(((t_andif *)node)->right);
	}
	if (node->type == N_OR)
	{
		ltree_free(((t_or *)node)->left);
		ltree_free(((t_or *)node)->right);
	}
	if (node->type != N_ANDIF && node->type != N_OR)
		free_bst((t_pipe *)root);
	else if (node->type == N_ANDIF || node->type == N_OR)
		free(root);
	return ;
}
