/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:45:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/07 15:17:24 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>


typedef	struct io
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
}

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;


// typedef struct minishell
// {
// 	char	*builtin_name;
// 	int		(*foo)(char **);
// }		t_buildin;


// typedef struct s_token
// {	
// 	char			*str;
// 	char			*str_backup;
// 	int				type;
// 	struct s_token	*prev;
// 	struct s_token	*next;
// }	t_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
	int		fdpipe[2];
}	t_io_fds;

typedef struct s_command
{
	// char				*command;
	char				*path;
	char				**args;
	// bool				pipe_output;
	// int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	// char		*user_input;
	// char		**env;
	// char		*working_dir;
	// char		*old_working_dir;
	// t_token		*token;
	t_command	*cmd;
	pid_t		pid;
	t_io_fds	io;
}	t_data;

void	execute(t_data *data, t_io_fds *io);


// /* ENUMS */
// enum e_token_types {
// 	SPACES = 1,
// 	WORD,
// 	PIPE,
// 	INPUT,
// 	TRUNC,
// 	HEREDOC,
// 	APPEND,
// 	END
// };

#endif