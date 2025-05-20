/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:30:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/30 11:39:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_heredoc_warning(t_in_out *io_here, int line_nbr)
{
	ft_putstr_fd("bash: warning: here-document at line ", \
	STDERR_FILENO);
	ft_putnbr_fd(line_nbr, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", \
	STDERR_FILENO);
	ft_putstr_fd(io_here->eof, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

static void	ft_put_heredoc(t_shell *shell, char *hd_l, int hd_fd, bool quoted)
{
	if (quoted == false)
		ft_heredoc_unquoted(shell, hd_l, hd_fd);
	else
		ft_putendl_fd(hd_l, hd_fd);
}

static bool	ft_is_delimiter(char *delimiter, char *hd_line)
{
	while (*hd_line)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*hd_line == *delimiter)
		{
			hd_line++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	if (!*delimiter)
		return (true);
	else
		return (false);
}

void	ft_heredoc_input(t_shell *sh, t_in_out *io_here, int hd_fd, bool quote)
{
	char	*hd_line;
	int		line_nbr;

	line_nbr = 1;
	while (g_signum != SIGINT)
	{
		hd_line = readline("> ");
		if (g_signum != SIGINT)
		{
			if (!hd_line)
			{
				ft_print_heredoc_warning(io_here, line_nbr);
				break ;
			}
			if (ft_is_delimiter(io_here->eof, hd_line) == true)
			{
				free(hd_line);
				break ;
			}
			ft_put_heredoc(sh, hd_line, hd_fd, quote);
			free(hd_line);
			line_nbr ++;
		}
	}
}
