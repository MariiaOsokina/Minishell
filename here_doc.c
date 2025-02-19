/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/19 14:15:38 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <structs.h>

void	ft_put_hd_line(char *hd_line, int fd_hd_w)
{
	int	i;

	i = 0;
	while (hd_line[i])
	{
		//handle here_doc expantion $ later
		ft_putchar_fd(hd_line[i], fd_hd_w);
		i++;
	}
	ft_putchar_fd('\n', fd_hd_w);
}

bool ft_is_delimiter(char *delimiter, char *hd_line)
{
	//to be added
	return (false);
}

int		ft_heredoc_fd(t_io *io) // with ft_heredo
{
	int fd_hd[2];
	int pid_hd;
	char *hd_line;
	//handle signals
	if (io->type ==  IO_HEREDOC)
	{
		pipe(fd_hd);
		pid_hd = fork();
		if (pid_hd == 0) //in here_doc child process
		{
			while(1)
			{
				hd_line = readline("> ");
				if (!hd_line)
					break ;
				if (ft_is_delimiter(io->value, hd_line))
					break;
				ft_put_hd_line(hd_line, fd_hd[1]); //put hd line to fd_hd[1];
				// to haddle edge cases
			}
		}
		io->fd_here_doc = fd_hd[0]; // for reading here-document from pipe
	}
	return (ENO_SUCCESS);
}
