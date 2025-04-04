/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:30:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/04 23:39:24 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	Function creates a name for the heredoc file. It will be a hidden file in the /temp
	folder. The static variable guarantees to have successive numbers.
 */

char	*ft_generate_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

/*
NOTE: 
- If the delimiter is quoted, the text in the here-document is taken literally,
w/o any expansions.
- If the delimiter is unquoted, the text in the here-document is subject to expansions.
*/

static bool 	ft_is_delimiter_quoted(char *delimiter)
{
	while(*delimiter)
	{
		if (*delimiter == '"' || *delimiter == '\'')
			return (true);
		delimiter ++;
	}
	return (false);
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

/*
function for filling heredoc tmp file (line by line):
1 -  check delimiter for quotes;
Infinity Loop: 
1 - readline (>);
2 - check signal CTRL + D if true then break loop;
3 - check "is delimiter" if true then break loop;
4 - put heredoc line to heredoc tmp file;
5 - free line as readline uses malloc;
*/

void	ft_fill_heredoc(t_in_out *io_here) 
{
	bool 	has_quoted;
	char 	*hd_line;
	int		line_nbr;
	int 	hd_fd;

	has_quoted = ft_is_delimiter_quoted(io_here->eof);
	line_nbr = 1;
	hd_fd = open(io_here->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_signals_heredoc();
	while(g_signum != SIGINT)
	{
		hd_line = readline("> ");
		if (g_signum != SIGINT)
		{
			if (!hd_line) // note: it happends in case of signal CTRL + D
			{
				ft_putstr_fd("bash: warning: here-document at line ", STDERR_FILENO);
				ft_putnbr_fd(line_nbr, STDERR_FILENO);
				ft_putstr_fd(" delimited by end-of-file (wanted \'", STDERR_FILENO);
				ft_putstr_fd(io_here->eof, STDERR_FILENO);
				ft_putstr_fd("\')\n", STDERR_FILENO);
				free(hd_line);
				break ;
			}
			if (ft_is_delimiter(io_here->eof, hd_line) == true)
			{
				free(hd_line);
				break ;
			}
			ft_put_heredoc_line(hd_line, hd_fd, has_quoted);
			free(hd_line);
			line_nbr ++;
		}
	}
	close(hd_fd);
	ft_signals_interactive();
}



/* if delimiter is not quoted(has_quoted = false):
- lines are subject to expansion;
- \n is ignored;
- \ for quoting characters \, $ and ` // to be check!!!
if delimiter is quoted(has_quoted = true):
- the text in the here-document is taken literally,*/


void	ft_put_heredoc_line(char *hd_line, int fd_hd, bool quoted)
{
	if (quoted == false)
	{
		// printf("Need to be no quotes rules\n");
		ft_heredoc_expander(hd_line, fd_hd);
	}
	else
		ft_putendl_fd(hd_line, fd_hd);
}


