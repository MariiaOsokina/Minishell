/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:09:53 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/30 00:24:53 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_cmd_path(char *cmd_name, t_list *path_list)
{
	char	*part_path;
	char	*full_path;

	while (path_list)
	{
		full_path = NULL;
		part_path = ft_strjoin(path_list->content, "/");
		full_path = ft_strjoin(part_path, cmd_name);
		free(part_path);
		if ((access(full_path, F_OK)) == 0)
			return (full_path);
		free(full_path);
		path_list = path_list->next;
	}
	return (NULL);
}

char	*ft_get_env_path(t_shell shell, char *cmd_name, t_err_no *err_no)
{
	char	*cmd_path;

	if (!ft_strcmp(cmd_name, "..") || !ft_strcmp(cmd_name, ""))
	{
		ft_err_msg(cmd_name, "command not found", NULL);
		*(err_no) = ENO_NOT_FOUND;
		return (NULL);
	}
	if (!ft_strcmp(cmd_name, "."))
	{
		ft_err_msg(cmd_name, "filename argument required", NULL);
		*(err_no) = 2;
		return (NULL);
	}
	cmd_path = ft_find_cmd_path(cmd_name, shell.path);
	if (!cmd_path)
	{
		ft_err_msg(cmd_name, "command not found", NULL);
		*(err_no) = ENO_NOT_FOUND;
		return (NULL);
	}
	*(err_no) = ENO_SUCCESS;
	return (cmd_path);
}
