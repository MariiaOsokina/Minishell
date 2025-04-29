/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:00:44 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/30 00:22:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_env_expand(t_shell *shell, char *str, size_t i, int fd)
{
	size_t	start;
	t_env	*tmp_env;
	char	*var;

	i += 1;
	start = i;
	var = NULL;
	if (str[i] == '?')
		return (ft_putnbr_fd(shell->exit_code, fd), 2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i != start)
		var = ft_substr(str, start, i - start);
	if (var)
	{
		tmp_env = ft_get_env_node(*shell, var);
		free(var);
		if (tmp_env && tmp_env->value)
			ft_putstr_fd(tmp_env->value, fd);
	}
	return (i - start + 1);
}

static void	ft_heredoc_esc_char(char *hd_line, int hd_fd, size_t *i)
{
	if (hd_line[*i] == '\\')
	{
		if (*i + 1 < ft_strlen(hd_line) && hd_line[*i + 1] && \
			(hd_line[*i + 1] == '$' || hd_line[*i + 1] == '\\' \
			|| hd_line[*i + 1] == '`'))
		{
			ft_putchar_fd(hd_line[*i + 1], hd_fd);
			*i += 2;
		}
		else
		{
			ft_putchar_fd('\\', hd_fd);
			(*i)++;
		}
	}
	return ;
}

void	ft_heredoc_unquoted(t_shell *shell, char *hd_line, int hd_fd)
{
	size_t	i;

	i = 0;
	while (hd_line[i])
	{
		if (hd_line[i] == '\\' && !hd_line[i + 1])
			return ;
		if (hd_line[i] == '\\')
			ft_heredoc_esc_char(hd_line, hd_fd, &i);
		else if (hd_line[i] == '$')
		{
			i += ft_heredoc_env_expand(shell, hd_line, i, hd_fd);
		}
		else
		{
			ft_putchar_fd(hd_line[i], hd_fd);
			i++;
		}
	}
	ft_putchar_fd('\n', hd_fd);
}
