/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:52 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/09 11:57:28 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO BE SOLVE:
- check that parsing checks the delimiter with closed quoutes, 
but saves delimiter WITH quotes in io_node.eof  ;
- REMOVE HEREDOC: use the unlink() function -> removes a file, 
parameter is	the path of the file.
- how to name tmp file, how to improve the security
*/

/* functions for generating heredocs:

loop the list of in out nodes and if in it is heredoc:

	1- generate the tmp file name for heredoc in /tmp/ directory;

	2- open fd(create heredoc tmp file and open it for write, chmod 0644); 
	//check?

	3 -fill heredoc tmp file line by line;

	4 - close tmp_fd;
*/
static void	ft_process_hd_pipe(t_shell *shell, t_pipe *pipe);
static void	ft_process_hd_andif(t_shell *shell, t_andif *andif);
static void	ft_process_hd_or(t_shell *shell, t_or *or);

void	ft_process_heredocs(t_shell *shell, void *node)
{
	t_node	*type_node;

	if (g_signum == SIGINT || !node)
		return ;
	type_node = (t_node *)node;
	if (type_node->type == N_ANDIF)
		ft_process_hd_andif(shell, (t_andif *)node);
	else if (type_node->type == N_OR)
		ft_process_hd_or(shell, (t_or *)node);
	if (type_node->type == N_PIPE)
		ft_process_hd_pipe(shell, (t_pipe *)node);
	else if (type_node->type == N_EXEC)
		ft_handle_heredocs(shell, (t_exec *)node);
	return ;
}

static void	ft_process_hd_pipe(t_shell *shell, t_pipe *pipe)
{
	if (pipe->left)
		ft_process_heredocs(shell, pipe->left);
	if (pipe->right && g_signum != SIGINT)
		ft_process_heredocs(shell, pipe->right);
}

static void	ft_process_hd_andif(t_shell *shell, t_andif *andif)
{
	if (andif->left && g_signum != SIGINT)
		ft_process_heredocs(shell, andif->left);
	if (andif->right && g_signum != SIGINT)
		ft_process_heredocs(shell, andif->right);
}

static void	ft_process_hd_or(t_shell *shell, t_or *or)
{
	if (or->left && g_signum != SIGINT)
		ft_process_heredocs(shell, or->left);
	if (or->right && g_signum != SIGINT)
		ft_process_heredocs(shell, or->right);
}

void	ft_handle_heredocs(t_shell *shell, t_exec *exec_node)
{
	t_list		*current;
	t_in_out	*io_node;
	char		*hd_arr_name;

	current = exec_node->in_out_list;
	while (current && g_signum != SIGINT)
	{
		io_node = (t_in_out *)current->content;
		if (io_node->type == HERE)
		{
			hd_arr_name = ft_generate_heredoc_name();
			ft_lstadd_back(&(shell->heredoc_names), ft_lstnew(hd_arr_name));
			io_node->name = ft_strdup(hd_arr_name);
			ft_fill_heredoc(io_node);
			printf("exit status after fill heredoc %d\n", shell->exit_code); //MO; for testing, to be deleted
			printf("g signum after fill heredoc %d\n", g_signum); //MO; for testing, to be deleted
		}
		current = current->next;
	}
	return ;
}

// void	ft_unlink_heredocs(t_list **heredoc_names)
// {
// 	t_list	*next;

// 	if (heredoc_names == NULL)
// 		return ;
// 	next = NULL;
// 	while (*heredoc_names)
// 	{
// 		next = (*heredoc_names)->next;
// 		if ((*heredoc_names)->content)
// 		{
// 			if (unlink((char *)(*heredoc_names)->content) != 0)
// 				ft_putstr_fd("unlink error\n", STDERR_FILENO);
// 		}
// 		*heredoc_names = next;
// 	}
// }

void	ft_unlink_heredocs(t_list *heredoc_names)
{
	if (heredoc_names == NULL)
		return ;
	while (heredoc_names)
	{
		if ((heredoc_names)->content)
		{
			if (unlink((char *)(heredoc_names)->content) != 0)
				ft_putstr_fd("unlink error\n", STDERR_FILENO);
		}
		heredoc_names = (heredoc_names)->next;
	}
}
