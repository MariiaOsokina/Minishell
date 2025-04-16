#include "minishell.h"


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

// void	free_outfile(void *content)
// {
// 	const t_outf	*outfile = (t_outf *)content;
// 	if (outfile)
// 	{
// 		free(outfile->name);
// 		free((void *)outfile);
// 	}
// }

// void	free_infile(void *content)
// {
// 	const t_inf	*infile = (t_inf *)content;

// 	if (infile)
// 	{
// 		free(infile->name);
// 		free(infile->eof);
// 		free((void *)infile);
// 	}
// }

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


void	free_exec(t_exec *node) //MO: added
{
	if (node)
	{
		// ft_free_str_arr(node->av, ft_arr_size(node->av));  //MO: added
		if (node->av)
			free(node->av);
		if (node->in_out_list)
			ft_lstclear(&node->in_out_list, free_int_out_list);
		free(node->in_out_list);
		free(node);
	}
}

// void	free_exec(t_exec *node)
// {
// 	if (node)
// 	{
// 		if (node->av)
// 			free(node->av);
// 		if (node->infiles)
// 			ft_lstclear(&node->infiles, free_infile);
// 		free(node->infiles);
// 		if (node->outfiles)
// 			ft_lstclear(&node->outfiles, free_outfile);
// 		free(node->outfiles);
// 		free(node);
// 	}
// }

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
	else if (node->type == N_ANDIF) //MO: fixed
		ltree_free((t_andif *)root);
	else if (node->type == N_OR)
		ltree_free((t_or *)root);
	return ;
}
