/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:52 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/02 13:00:13 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO BE SOLVE:
- check that parsing checks the delimiter with closed quoutes, but saves delimiter WITH quotes in io_node.eof  ;
- REMOVE HEREDOC: use the unlink() function -> removes a file, parameter is	the path of the file.
- how to name tmp file, how to improve the security
*/

/* functions for generating heredocs:

loop the list of in out nodes and if in it is heredoc:

	1- generate the tmp file name for heredoc in /tmp/ directory;

	2- open fd(create heredoc tmp file and open it for write, chmod 0644); //check?

	3 -fill heredoc tmp file line by line;

	4 - close tmp_fd;
*/

void ft_handle_heredocs(t_shell *shell, void *node)
{
	t_node *type_node;

	if (g_signum == SIGINT || !node)
		return ;
	type_node = (t_node*)node;
	if (type_node->type == N_ANDIF)
		ft_handle_heredocs_andif(shell, (t_andif *)node);
	else if  (type_node->type == N_OR)
		ft_handle_heredocs_or(shell, (t_or *)node);
	if (type_node->type == N_PIPE)
		ft_handle_heredocs_pipe(shell, (t_pipe *)node);
	else if (type_node->type == N_EXEC)
		ft_generate_heredocs(shell, (t_exec *)node);
	return ;
}

void	ft_handle_heredocs_pipe(t_shell *shell, t_pipe *pipe)
{
    if (pipe->left)
		ft_handle_heredocs(shell, pipe->left);
    if (pipe->right && g_signum != SIGINT)
		ft_handle_heredocs(shell, pipe->right);
}

void	ft_handle_heredocs_andif(t_shell *shell, t_andif *andif)
{
    if (andif->left && g_signum != SIGINT)
		ft_handle_heredocs(shell, andif->left);
    if (andif->right && g_signum != SIGINT)
		ft_handle_heredocs(shell, andif->right);
}

void	ft_handle_heredocs_or(t_shell *shell, t_or *or)
{
    if (or->left && g_signum != SIGINT)
		ft_handle_heredocs(shell, or->left);
    if (or->right && g_signum != SIGINT)
		ft_handle_heredocs(shell, or->right);
}

void	ft_generate_heredocs(t_shell *shell, t_exec *exec_node)
{
	(void)shell;
	t_list		*current;
	t_in_out 	*io_node;

	current = exec_node->in_out_list;
	while (current && g_signum != SIGINT)
	{
		io_node = (t_in_out *)current->content;
		if (io_node->type == HERE)
		{
			io_node->name = ft_generate_heredoc_name();
			ft_lstadd_back(&(shell->heredoc_names), ft_lstnew(io_node->name));
			ft_fill_heredoc(shell, io_node);
			printf("exit status after fill heredoc %d\n", shell->exit_code); //MO; for testing, to be deleted
			printf("g signum after fill heredoc %d\n", g_signum); //MO; for testing, to be deleted
		}
		current = current->next;
	}
	return ;
}
