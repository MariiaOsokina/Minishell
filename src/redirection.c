/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:39:40 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 13:37:40 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

/*STEPS:
LOOP thoought the list of in_out nodes and  based on type:
1 - If fd_in (<)
	a - check "ambigunous redirect" (it occurs if after expansion there're 
	more than one filename *wildcards <*inf or empty filename )
	b - open file with flag O_RDONLY + check the access (existance and permission)
 	c - dup2(fd, STDIN) and close fd;
2- If fd_out(>)
	a - check "ambigunous redirect" (case: e.g.,  if after expansion, more that one filename *wildcards,empty filename) 
	b - open with flags (O_CREAT | O_WRONLY | O_TRUNC)  + check access (file’s existance and permission)
	create the file (with mode 0664) if it doesn’t exist, open it for writing only, and TRUNCATE it to zero length
 	c - dup2(fd, STDOUT) and close fd;
3 - If fd_append (>>) 
	a - check "ambigunoous redirect"  (case: e.g.,  if after expansion, more that one filename *wildcards,empty filename) 
	b - open with flags  (O_CREAT | O_WRONLY | O_APPEND)  + check access (file’s existance and permission)
	create the file (with mode 0664) if it doesn’t exist, open it for writing only, and APPEND it
	c - dup2(fd, STDOUT) and close fd;
4	- 	If case of an error with in(<), out(>) or append(>>) (i.e. exit status is not SUCCESS) the redirection fails and stops
		and return should be with teh exit status 1.
5	- 	If here_doc(<<)
	a - NOTE: Input was written to heredoc's fd BEFORE redirection!
	b - dup2(fd_heredoc[1], STDIN) and close ??fd_heredoc[1];
*/

/*TESTS
1 - writting to the last file
$ls >outfile1 >outfile2
$cat outfile1
$ cat outfile2
a.out
builtins


1a - reading from the last file
$ls <infile1 <infile2
infile2

2 - order of looping
$>/nodir/outfile <infile ls
bash: /nodir/outfile: No such file or directory

<infile >/nodir/outfile 
//bash: infile: No such file or directory

3 - exit code 1
$>/nodir/outfile <infile ls
$echo $?
1
*/

int	ft_redirection(t_exec *exec_node)
{
	t_list		*tmp_io_list;
	int			tmp_status;
	t_in_out 	*in_out_node;

	tmp_io_list = exec_node->in_out_list;
	tmp_status = ENO_SUCCESS;
	while(tmp_io_list)
	{
		in_out_node = (t_in_out*)tmp_io_list->content;
		if (in_out_node->type == INF)
			tmp_status = ft_redir_inf(in_out_node);
		else if (in_out_node->type == ADD || in_out_node->type == APP)
			tmp_status = ft_redir_outf(in_out_node);		
		// else if (in_out_node->type == ADD)
		// 	tmp_status = ft_redir_outf(in_out_node);
		// else if (in_out_node->type == APP)
			// tmp_status = ft_redir_append(in_out_node);
		//heredoc - to be tested later!!!
		else if (in_out_node->type == HERE)
		{
			dup2(STDIN_FILENO, in_out_node->fd_heredoc);
			close(in_out_node->fd_heredoc);
		}
		if (tmp_status != ENO_SUCCESS)
			return (tmp_status);
		tmp_io_list = tmp_io_list->next;
	}
	return (tmp_status);
}

int		ft_redir_inf(t_in_out	*in_out_node)
{
	int fd;
	char *file;

	if (!in_out_node->expanded_name || in_out_node->expanded_name[1])
	{
		ft_err_msg (in_out_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL);
	}
	file = in_out_node->expanded_name[0];
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

int		ft_redir_outf(t_in_out *in_out_node)
{
	int fd;
	char *file;

	if (!in_out_node->expanded_name || in_out_node->expanded_name[1])
	{
		ft_err_msg (in_out_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL);
	}
	file = in_out_node->expanded_name[0];
	if (in_out_node->type == ADD)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
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
