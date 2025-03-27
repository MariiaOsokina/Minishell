/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:52 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/27 14:10:22 by mosokina         ###   ########.fr       */
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

	if (!node)
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
    if (pipe->right)
		ft_handle_heredocs(shell, pipe->right);
}

void	ft_handle_heredocs_andif(t_shell *shell, t_andif *andif)
{
    if (andif->left)
		ft_handle_heredocs(shell, andif->left);
    if (andif->right)
		ft_handle_heredocs(shell, andif->right);
}

void	ft_handle_heredocs_or(t_shell *shell, t_or *or)
{
    if (or->left)
		ft_handle_heredocs(shell, or->left);
    if (or->right)
		ft_handle_heredocs(shell, or->right);
}

void	ft_generate_heredocs(t_shell *shell, t_exec *exec_node)
{
	(void)shell;
	int		tmp_fd;
	t_list *current;
	t_in_out *io_node;

	current = exec_node->in_out_list;
	while (current)
	{
		io_node = (t_in_out *)current->content;
		if (io_node->type == HERE)
		{
			io_node->name = ft_generate_heredoc_name();
			tmp_fd = open(io_node->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			ft_fill_heredoc(io_node, tmp_fd);
			close(tmp_fd);
		}
		current = current->next;
	}
	return ;
}


// void	signal_ctlc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDERR_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	signal_ctlc_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		close(STDIN_FILENO);
// 		write(STDERR_FILENO, "\n", 1);
// 	}
// }


// int	termios_change(bool echo_ctl_chr)
// {
// 	struct termios	terminos_p;
// 	int				status;

// 	status = tcgetattr(STDOUT_FILENO, &terminos_p);
// 	if (status == -1)
// 		return (ERROR);
// 	if (echo_ctl_chr)
// 		terminos_p.c_lflag |= ECHOCTL;
// 	else
// 		terminos_p.c_lflag &= ~(ECHOCTL);
// 	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
// 	if (status == -1)
// 		return (ERROR);
// 	return (0);
// }
//ioctl(0, TIOCSTI, "\n");