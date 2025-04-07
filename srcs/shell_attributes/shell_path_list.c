/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_path_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:46:59 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/06 11:50:41 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_path_list(t_shell *shell)
{
	t_list	*path_list;
    t_env   *path_env;
	char	*path;
	int		i;

	path_list = NULL;
    path_env = ft_get_env_node(*shell, "PATH");
    if (!path_env || !path_env->value)
        return (NULL);
    path = path_env->value;
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
		i = ft_get_path(shell, &path_list, path, i);
	return (path_list);
}

int	ft_get_path(t_shell *shell, t_list **path_list, char *path, int i)
{
	char	*new_path;
	int		start;

	start = i;
	while (path[i] && path[i] != ':')
		i++;
	new_path = ft_substr(path, start, i - start);
	if (!new_path)
        exit_failure(shell, "get_path");
	ft_lstadd_back(path_list, ft_lstnew(new_path));
	if (path[i] == ':')
		i++;
	return (i);
}
