/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/06 00:14:32 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <structs.h>

void	ft_put_hd_line(char *hd_line, int fd_hd_w)
{
	int	i;

	i = 0;
	while (hd_line[i])
	{
		//handle here_doc expansion $ later
		ft_putchar_fd(hd_line[i], fd_hd_w);
		i++;
	}
	ft_putchar_fd('\n', fd_hd_w);
}


// "bash: warning: here-document at line 7 delimited by end-of-file (wanted `delim')"

// cat <<delim
// > test
// > test
// > 
// bash: warning: here-document at line 8 delimited by end-of-file (wanted `delim')
// test
// test
// mosokina@c1r5s2:~/MY_42/MINISHELL/minishell_github/tests$ ^C

bool ft_is_delimiter(char *delimiter, char *hd_line)
{
	if (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	if (ft_strcmp(hd_line, delimiter) != 0)
		return (true);
	else
		return(false);
}

int		ft_heredoc_fd(t_io *io) 
{
	int fd_hd[2];
	int pid_hd;
	char *hd_line;
	int tmp_status;
	//handle signals //QUIT SHOULD BE IGNORED in PARENT PROCESS!
	if (io->type ==  IO_HEREDOC)
	{
		pipe(fd_hd);
		pid_hd = fork();
		if (pid_hd == 0) //in here_doc child process
		{
			//skip quotes??
			while(1)
			{
				hd_line = readline("> ");
				if (!hd_line) // ctrl + d CASE
				{
					// ft_putstr_fd(STDERR, "\nbash: warning: here-document at line 16 delimited by end-of-file (\'")
					// ft_putstr_fd(STDERR, delimeter);
					// ft_putstr_fd(STDERR, "\')\n");
					break ;
				}
				if (ft_is_delimiter(io->value, hd_line))
					break ;
				ft_put_hd_line(hd_line, fd_hd[1]); //put hd line to fd_hd[1];
				// to haddle edge cases
			}
		}
		waitpid(pid_hd, &tmp_status, NULL); //tmp_st??
		//close fd_hd[1] ???
		io->fd_here_doc = fd_hd[0]; // for reading here-document from pipe
	}
	return (ENO_SUCCESS);
}
