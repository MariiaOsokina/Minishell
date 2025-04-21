#include "minishell.h"

void	free_in_outfiles(void *content)
{
	const t_in_out	*in_ofiles = (t_in_out *)content;

	if (in_ofiles)
	{
		if (in_ofiles->name)
			free(in_ofiles->name);
		if (in_ofiles->expanded_name)
			free(in_ofiles->expanded_name);
		if (in_ofiles->eof)
			free(in_ofiles->eof);
		free((void *)in_ofiles);
	}
}

void	free_sub_pipes(t_pipe *pipe)
{
	if (pipe)
	{
		if (pipe->left)
			ltree_free(pipe->left);
		if (pipe->right)
			ltree_free(pipe->right);
	}
	free(pipe);
}

void	free_exec(t_exec *node)
{
	if (node)
	{
		if (node->command)
			free(node->command);
		if (node->av)
			free(node->av);
		if (node->i_ofiles)
			ft_lstclear(&node->i_ofiles, free_in_outfiles);
		free(node);
	}
}

void	free_bst(void *root)
{
	t_node	*node;

	if (!root)
		return ;
	node = (t_node *)root;
	if (node->type == N_PIPE)
		free_sub_pipes((t_pipe *)root);
	else if (node->type == N_EXEC)
		free_exec((t_exec *)root);
	else if (node->type == AND_IF)
		ltree_free((t_andif *)root);
	else if (node->type == N_OR)
		ltree_free((t_or *)root);
	return ;
}
