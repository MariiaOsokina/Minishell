/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:00:44 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/04 20:02:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if delimiter is not quoted(has_quoted = false):
- lines are subject to expansion;
- \n is ignored;
- \ for quoting characters \, $ and ` // to be check!!!
*/

char *ft_hd_line_expansion(char *hd_line)
{
	//to be done
	return (hd_line);
}

void	ft_heredoc_expander(char *hd_line, int fd_hd)
{
	int	i;

	i = 0;
	while (hd_line[i])
	{
		// if (hd_line[i] == '\')
		// 	i ++;
		// if next \ n $ or ' write 2d if not skip 1st??
		if (hd_line[i] == '$')
			// i += ft_heredoc_expand_writer(hd_line, i, fd_hd);
			i++;
		else
			i += (ft_putchar_fd(hd_line[i], fd_hd), 1);
	}
	ft_putchar_fd('\n', fd_hd);
}

// static int	ft_heredoc_expand_writer(char *str, size_t i, int fd)
// {
// 	size_t	start;
// 	char	*tmp;

// 	start = ++i;
// 	if (str[i] == '?')
// 		return (ft_putnbr_fd(g_minishell.exit_s, fd), 2);
// 	while (str[i] && str[i] != '$' && str[i] != ' ')
// 		i++;
// 	if (i != start)
// 	{
// 		tmp = ft_garbage_collector(ft_substr(str, start, i), false);
// 		tmp = ft_get_envlst_val(tmp);
// 		if (tmp)
// 			ft_putstr_fd(tmp, fd);
// 	}
// 	return (i);
// }
