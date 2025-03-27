/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/27 14:10:22 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO BE SOLVED:
- subshell for parenhtesis*/

void	ft_start_execution(t_shell *shell)
{
	// set_main_signals();
//     signal(SIGQUIT, ft_sigquit_handler); //activate SIGQUIT NOT INTERACTIVE MODE
	//to think the proper order
	//if signal ctrl + C:inside heredoc:
		//1-	save  exit code = 130 
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
