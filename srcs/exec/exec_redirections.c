/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:39:40 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 19:48:32 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_inf(t_shell *shell, t_in_out	*in_out_node)
{
	int		fd;
	char	*file;

	if (in_out_node->type != HERE)
	{
		if (ft_expand_redir_name(shell, in_out_node) != ENO_SUCCESS)
			return (ENO_GENERAL);
	}
	file = in_out_node->name;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_err_msg(file, strerror(errno), NULL);
		return (ENO_GENERAL);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (ENO_SUCCESS);
}

static int	ft_redir_outf(t_shell *shell, t_in_out *in_out_node)
{
	int		fd;
	char	*file;

	if (ft_expand_redir_name(shell, in_out_node) != ENO_SUCCESS)
		return (ENO_GENERAL);
	file = in_out_node->name;
	if (in_out_node->type == ADD)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_err_msg(file, strerror(errno), NULL);
		return (ENO_GENERAL);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (ENO_SUCCESS);
}

int	ft_redirections(t_shell *shell, t_exec *exec_node)
{
	t_list		*tmp_io_list;
	int			tmp_status;
	t_in_out	*in_out_node;

	tmp_io_list = exec_node->i_ofiles;
	tmp_status = ENO_SUCCESS;
	while (tmp_io_list)
	{
		in_out_node = (t_in_out *)tmp_io_list->content;
		if (in_out_node->type == INF || in_out_node->type == HERE)
			tmp_status = ft_redir_inf(shell, in_out_node);
		else if (in_out_node->type == ADD || in_out_node->type == APP)
			tmp_status = ft_redir_outf(shell, in_out_node);
		if (tmp_status != ENO_SUCCESS)
			return (tmp_status);
		tmp_io_list = tmp_io_list->next;
	}
	return (tmp_status);
}
