#include "minishell.h"

/*
void	free_int_out_list(void *content) //MO: added
{
	const t_in_out	*io_node = (t_in_out *)content;
	if (io_node)
	{
		if (io_node->eof)
			free(io_node->eof);
		if (io_node->name)
			free(io_node->name);
		free((void *)io_node);
	}
}
*/

void	free_in_outfiles(void *content)
{
	const t_in_out	*in_ofiles = (t_in_out *)content;

	if (in_ofiles)
	{
		if (in_ofiles->name)
			free(in_ofiles->name);
		// if (in_ofiles->expanded_name)
		// 	free(in_ofiles->expanded_name);
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

/*
void	free_exec(t_exec *node) //MO: added
{
	if (node)
	{
		if (node->command)
			free(node->command);
		// if (node->av)
		// 	free(node->av);
		if (node->av)
			ft_free_str_arr(node->av, ft_arr_size(node->av));  //MO: added
		if (node->i_ofiles)
			ft_lstclear(&node->i_ofiles, free_int_out_list);
		free(node->i_ofiles);
		free(node);
	}
}
*/

void	free_exec(t_exec *node)
{
	int	i;

	i = 0;
	if (node)
	{
		if (node->command)
			free(node->command);
		if (node->av)
		{
			while(node->av[i])
				free(node->av[i++]);
			free(node->av);
			node->av = NULL;
		}
		if (node->i_ofiles)
		{
			ft_lstclear(&node->i_ofiles, free_in_outfiles);
			// node->i_ofiles = NULL;
		}
		free(node->i_ofiles); // MO addded;
		free(node);
	}
}

void	free_bst(void *root) //MO CHECK THE LOGIC OF THE FUNCTION? SIMPLIFY?
{
	t_node	*node;

	if (!root)
		return ;
	node = (t_node *)root;
	if (node->type == N_PIPE)
		free_sub_pipes((t_pipe *)root);
	else if (node->type == N_EXEC)
		free_exec((t_exec *)root);
	else if (node->type == N_ANDIF)
		ltree_free((t_andif *)root);
	else if (node->type == N_OR)
		ltree_free((t_or *)root);
	return ;
}
