/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/26 15:28:13 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO BE SOLVED:
- subshell for parenhtesis*/

void	ft_start_execution(t_shell *shell)
{
	// set_main_signals();
//     signal(SIGQUIT, ft_sigquit_handler); //activate SIGQUIT NOT INTERACTIVE MODE
	ft_handle_heredocs(shell, shell->root);//to think the proper order
	printf("test: resady to execute\n");
	//inside save io_list(HERE_DOC) save all heredocs
	//if signal ctrl + C:inside heredoc:
		//1-save  exit code = 130 
		//2 - clear ast and this iteration's history;
		//3 and continue in while (1)(i.e. stop this iteration and move n to next iteration)
	shell->exit_code = ft_exec_node(shell, shell->root);
}

int ft_exec_node(t_shell *shell, void *node)
{
	t_node *type_node;
	int		tmp_status;

	tmp_status = ENO_SUCCESS;
	type_node = (t_node*)node;
	if (type_node->type == N_ANDIF)
		tmp_status = ft_exec_andif(shell, (t_andif *)node);
	else if  (type_node->type == N_OR)
		tmp_status = ft_exec_or(shell, (t_or *)node);
	else if (type_node->type == N_PIPE)
	{
		tmp_status = ft_exec_pipeline(shell, (t_pipe *)node);
		return (tmp_status);
	}
	else if (type_node->type == N_EXEC) 
	{
		tmp_status = ft_exec_simple_cmd(shell, (t_exec *)node);
		return (tmp_status);
	}
	return (tmp_status);
}

int ft_exec_andif(t_shell *shell, t_andif *andif_node)
{
	int		tmp_status;

	tmp_status = ft_exec_node(shell, andif_node->left);
	if (tmp_status == ENO_SUCCESS)
		tmp_status= ft_exec_node(shell, andif_node->right);
	return (tmp_status);
}

int ft_exec_or(t_shell *shell, t_or *or_node)
{
	int		tmp_status;

	tmp_status = ft_exec_node(shell, or_node->left);
	if (tmp_status != ENO_SUCCESS)
		tmp_status= ft_exec_node(shell, or_node->right);
	return (tmp_status);
}






/*
Will be used in exec???
int	handle_exec_node(t_shell *shell, void *root, int *status)
{
	t_exec	*exec;

	exec = NULL;
	if (((t_node *)root)->type == N_EXEC)
	{
		exec = (t_exec *)root;
		if (is_parent_builtin(exec))
		{
			exec->av = expand_av(shell, exec->av);
			exec_parent_builtin(shell, exec);
			free_expanded(exec->av);
			return (1);
		}
		else
		{
			if (fork() == 0)
				exec_tree(shell, root);
			waitpiad(-1, status, 0);
			return (1);
		}
	}
	return (0);
}

void	exec_processes(t_shell *shell, void *root)
{
	int	status;

	status = 0;
	set_main_signals();
	handle_heredoc();
	if (handle_exec_node(shell, root, &status))
		return ;
	if (fork() == 0)
		exec_tree(shell, root);
	waitpid(-1, &status, 0);
	exit_status(status);
}
*/

/*

static void	ft_init_exec_node(t_exec *exec_node)
{
	t_list	*current;
	t_in_out *io_node;

	if (exec_node->av)
		exec_node->av = ft_expand(exec_node->av);
	current = exec_node->in_out_list;
	ft_handle_heredocs(exec_node); //to think the proper order
	while (current)
	{
		io_node = (t_in_out *)current->content;
		if (io_node->type != HERE)
			io_node->expanded_name = ft_expand(io_node->name);
		current = current->next;
	}
}
*/