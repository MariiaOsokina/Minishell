/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:39:40 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/17 01:29:50 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int	redirection(t_node *cmd) //?? node instead cmd
{
	t_list	*tmp_io_list;
	int		tmp_status;
	t_io 	*tmp_io;

	tmp_io_list = cmd->io_list;
	while(tmp_io_list)
	{
		tmp_io = (t_io*)tmp_io_list->content;
		if (tmp_io->type == IO_IN)
			tmp_status = ft_in(tmp_io);
		else if (tmp_io->type == IO_OUT)
			tmp_status = ft_out(tmp_io);
		else if (tmp_io->type == IO_APPEND)
			tmp_status = ft_append(tmp_io);
		//heredoc???
		if (tmp_status != ENO_SUCCESS)
			return (tmp_status);
		tmp_io_list = tmp_io_list->next;
	}
	return (ENO_SUCCESS);
}

int		ft_in(t_io	*io)
{
	//need to be tested
    int fd;
	char *file;

	file = io->expanded_value;
	if (!file || file[1])
	{
		ft_err_msg (io->value, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL);
	}
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

int		ft_out(t_io *io)
{
	//in progress
    return(ENO_SUCCESS);
}

int		ft_append(t_io *io)
{
	// in progress
    return(ENO_SUCCESS);
}

// heredoc
