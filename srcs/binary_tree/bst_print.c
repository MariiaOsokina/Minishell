#include "minishell.h"

void	print_sub_pipe(t_pipe *pipe, int space)
{
	if (pipe->right)
		print_bst(pipe->right, space);
	print_bst_pipe(pipe, space);
	if (pipe->left)
		print_bst(pipe->left, space);
}

void	print_bst_pipe(t_pipe *node, int space)
{
	int	i;

	i = -1;
	printf("\n");
	while (++i < space)
		printf(" ");
	if (node->type.type == N_PIPE)
		printf("[PIPE]\n");
}

void	print_bst_exec(t_exec *node, int space)
{
	int	i;

	i = -1;
	if (node->outfiles)
		print_outfiles(node->outfiles, space);
	while (++i < space)
		printf(" ");
	printf("[EXEC]\n");
	if (node->av)
		print_exec(node->av, space);
	if (node->infiles)
		print_infiles(node->infiles, space);
}

void	print_exec(char **av, int space)
{
	int	i;
	int	j;

	j = -1;
	while (av[++j])
	{
		i = -1;
		while (++i < space + 2)
			printf(" ");
		printf("[%s]\n", av[j]);
	}
}

void	*print_bst(void *root, int space)
{
	t_node	*node;
	int	spacing;

	if (space == 5)
		printf("\n\n\nTREE VIEW:\n");
	spacing = 5;
	space += spacing;
	if (!root)
		return (NULL);
	node = (t_node *)root;
	if (node->type == N_PIPE)
		print_sub_pipe((t_pipe *)root, space);
	else if (node->type == N_EXEC)
		print_bst_exec((t_exec *)root, space);
	else if (node->type == N_ANDIF)
		ltree_print((t_andif *)root, space);
	else if (node->type == N_OR)
		ltree_print((t_or *)root, space);
	return (NULL);
}
