/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:26:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/10 14:30:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_heredoc_warning(t_in_out *io_here, int line_nbr)
{
	ft_putstr_fd("bash: warning: here-document at line ", \
	STDERR_FILENO);
	ft_putnbr_fd(line_nbr, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", \
	STDERR_FILENO);
	ft_putstr_fd(io_here->eof, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

void	ft_put_heredoc(t_shell *shell, char *hd_l, int hd_fd, bool has_quoted)
{
	if (has_quoted == false)
		ft_heredoc_unquoted(shell, hd_l, hd_fd);
	else
		ft_putendl_fd(hd_l, hd_fd);
}

void	ft_heredoc_input(t_shell *sh, t_in_out *io_here, int hd_fd, bool quoted)
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
			ft_put_heredoc(sh, hd_line, hd_fd, quoted);
			free(hd_line);
			line_nbr ++;
		}
	}
}

void	ft_fill_heredoc(t_shell *shell, t_in_out *io_here)
{
	bool	has_quoted;
	int		hd_fd;

	has_quoted = ft_is_delimiter_quoted(io_here->eof);
	hd_fd = open(io_here->name, O_CREAT | O_WRONLY | O_TRUNC, 0644); //check?
	ft_signals_heredoc();
	ft_heredoc_input(shell, io_here, hd_fd, has_quoted);
	close(hd_fd);
	ft_signals_interactive();
}
