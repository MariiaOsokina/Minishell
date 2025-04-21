#include "minishell.h"

int	get_av_len(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	print_i_ofiles(t_list *in_ofiles, int space)
{
	int	i;

	i = 0;
	while (i < space + 2)
	{
		printf(" ");
		i++;
	}
	printf("[IN_OUT_FILES]: ");
	i = 0;
	while (in_ofiles)
	{
		printf("%s", (char *)((t_in_out *)in_ofiles->content)->name);
		if (in_ofiles->next)
			printf(", ");
		in_ofiles = in_ofiles->next;
	}
	printf("\n");
}

void	free_ast_node(void *node)
{
	if (!node)
		return ;
	if (((t_node *)node)->type == N_PIPE)
	{
		free_ast_node(((t_pipe *)node)->right);
		free_ast_node(((t_pipe *)node)->left);
	}
	else if ((((t_node *)node)->type == N_ANDIF
			|| (((t_node *)node)->type == N_OR)))
	{
		free_ast_node(((t_op *)node)->right);
		free_ast_node(((t_op *)node)->left);
	}
	free(node);
}
