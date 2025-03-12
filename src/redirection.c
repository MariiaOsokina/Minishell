/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:39:40 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/12 15:59:07 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

/*Redirections:
LOOP in_out nodes in the list,  depended on type:
1 - If fd_in (<)
	a - check “"ambigunous redirect" (if after expansion - more that one filename *wildcards,empty filename <*inf)
	b - open file with flags- O_RDONLY) + check the access (existance and permission)
 	c - dup2(fd, STDIN)
	d - Close fd;
2- If fd_out(>)
	a - check “"ambigunoous redirect" (case: e.g.,  if after expansion, more that one filename *wildcards,empty filename) 
	b - open with flags (O_CREAT | O_WRONLY | O_TRUNC)  + check access (file’s existance and permission)
	create the file if it doesn’t exist, open it for writing only, and TRUNCATE it to zero length
 	c - dup2(fd, STDOUT)
	d - Close fd;
3 - If fd_append (>>) 
	a - check “"ambigunoous redirect"  (case: e.g.,  if after expansion, more that one filename *wildcards,empty filename) 
	b - open with flags  (O_CREAT | O_WRONLY | O_APPEND)  + check access (file’s existance and permission)
	create the file if it doesn’t exist, open it for writing only, and APPEND it
	c - dup2(fd, STDOUT)
	d - Close fd;
4	- 	If error with in(<), out(>) or append(>>) (exit status is not SUCCESS) the redirection fails and return with exit status 1.
5	- 	If here_doc(<<)
	a - Input was written to fd_hd before redirection!
	b - dup2(fd_hd[1], STDIN)
	c - Close fd_hd[1];
*/

int	redirection(t_exec *exec_node)
{
	t_list		*tmp_io_list;
	int			tmp_status;
	t_in_out 	*in_out_node;

	tmp_io_list = exec_node->in_out_list;
	while(tmp_io_list)
	{
		in_out_node = (t_in_out*)tmp_io_list->content;
		if (in_out_node->type == INF)
			tmp_status = ft_in(in_out_node);
		else if (in_out_node->type == ADD)
			tmp_status = ft_out(in_out_node);
		else if (in_out_node->type == APP)
			tmp_status = ft_append(in_out_node);

		if (tmp_status != ENO_SUCCESS)
			return (tmp_status);
		//heredoc - to be tested!!!
		else if (in_out_node->type == HERE)
		{
			dup2(STDIN_FILENO, in_out_node->fd_heredoc);
			close(in_out_node->fd_heredoc);
		}
		tmp_io_list = tmp_io_list->next;
	}
	return (ENO_SUCCESS);
}

int		ft_in(t_in_out	*in_out_node)
{
	int fd;
	char *file;

	if (!in_out_node->expended_name || in_out_node->expended_name[1])
	{
		ft_err_msg (in_out_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL);
	}
	file = in_out_node->expended_name[0];
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (access(file, R_OK) == -1) // file doesn't exist
			ft_err_msg (file, "No such file or directory", NULL);
		else // file doesn't permission;
			ft_err_msg (file, " Permission denied", NULL);
		return (ENO_GENERAL);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (ENO_SUCCESS);
}

int		ft_out(t_in_out *in_out_node)
{
	int fd;
	char *file;

	if (!in_out_node->expended_name || in_out_node->expended_name[1])
	{
		ft_err_msg (in_out_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL);
	}
	file = in_out_node->expended_name[0];
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (access(file, R_OK) == -1) // file doesn't exist
			ft_err_msg (file, "No such file or directory", NULL);
		else // no permission;
			ft_err_msg (file, " Permission denied", NULL);
		return (ENO_GENERAL);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
    return(ENO_SUCCESS);
}

int		ft_append(t_in_out *in_out_node)
{
	int fd;
	char *file;

	if (!in_out_node->expended_name || in_out_node->expended_name[1])
	{
		ft_err_msg (in_out_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL);
	}
	file = in_out_node->expended_name[0];
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644); 

	if (fd == -1)
	{
		if (access(file, R_OK) == -1) // file doesn't exist
			ft_err_msg (file, "No such file or directory", NULL);
		else // no permission;
			ft_err_msg (file, " Permission denied", NULL);
		return (ENO_GENERAL);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
    return(ENO_SUCCESS);
}
