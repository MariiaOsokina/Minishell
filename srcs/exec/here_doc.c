/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:52 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/26 00:38:51 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// /*TO BE SOLVE:
// - check that parsing checks the delimiter with closed quoutes, but saves delimiter WITH quotes in io_node.eof  ;
// - REMOVE HEREDOC: use the unlink() function -> removes a file, parameter is	the path of the file.
// - how to name tmp file, how to improve the security
// */

// /* functions for generating heredocs:

// loop the list of in out nodes in case of heredoc:

// 	1- generate the name for heredoc tmp file;

// 	2- open fd(create heredoc tmp file and open it for write, chmod 0644); //check?

// 	3 -fill heredoc tmp file line by line;

// 	4 - close tmp_fd;
// */

// /* 
// 	creates a name for the heredoc file. It will be a hidden file in the /temp
// 	folder. the static variable guarantees to have successive numbers.
//  */
// static char	*ft_generate_heredoc_name(void)
// {
// 	static int	i;
// 	char		*name;
// 	char		*number;

// 	number = ft_itoa(i);
// 	if (!number)
// 		return (NULL);
// 	name = ft_strjoin(HEREDOC_NAME, number);
// 	free(number);
// 	i++;
// 	return (name);
// }

// int	ft_handle_heredocs(t_exec *exec_node)
// {
// 	int		tmp_fd;
// 	t_list *current;
// 	t_in_out *io_node;

// 	exec_node->in_out_list = current;
// 	while (current)
// 	{
// 		io_node = (t_in_out *)current->content;
// 		if (io_node->type == HERE)
// 		{
// 			io_node->name = ft_generate_heredoc_name();
// 			tmp_fd = open(io_node->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			ft_fill_heredoc(io_node, tmp_fd);
// 			close(tmp_fd);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

// /*
// NOTE: 
// - If the delimiter is quoted, the text in the here-document is taken literally,
// w/o any expansions.
// - If the delimiter is unquoted, the text in the here-document is subject to expansions.
// */

// bool 	ft_is_delimiter_quoted(char *delimiter)
// {
// 	while(*delimiter)
// 	{
// 		if (*delimiter == '"' || *delimiter == '\'')
// 			return (true);
// 		delimiter ++;
// 	}
// 	return (false);
// }

// /*
// function for filling heredoc tmp file (line by line):
// 1 -  check delimiter for quotes;
// Infinity Loop: 
// 1 - readline (>);
// 2 - check signal CTRL + D if true then break loop;
// 3 - check "is delimiter" if true then break loop;
// 4 - put heredoc line to heredoc tmp file;
// 5 - free line as readline uses malloc;
// */

// int		ft_fill_heredoc(t_in_out *io_here, int fd_hd) 
// {
// 	bool 	has_quoted;
// 	char 	*hd_line;
// 	int		line_nbr;

// 	line_nbr = 0;
// 	has_quoted = ft_is_delimiter_quoted(io_here->eof);
// 	//handle signals //QUIT SHOULD BE IGNORED in PARENT PROCESS!
// 	while(1)
// 	{
// 		hd_line = readline("> "); // MALLOC!!!!
// 		if (!hd_line) // note: it happends in case of signal CTRL + D
// 		{
// 			ft_putstr_fd(STDERR_FILENO, "\nbash: warning: here-document at line ");
// 			ft_putnbr_fd(STDERR_FILENO, line_nbr);
// 			ft_putstr_fd(STDERR_FILENO,  "delimited by end-of-file (\'");
// 			ft_putstr_fd(STDERR_FILENO, io_here->eof);
// 			ft_putstr_fd(STDERR_FILENO, "\')\n");
// 			break ;
// 		}
// 		if (ft_is_delimiter(io_here->eof, hd_line))
// 			break ;
// 		ft_put_heredoc_line(hd_line, fd_hd, has_quoted);
// 		free(hd_line);
// 		line_nbr ++;
// 	}
// 	return (0);
// }

// char *ft_line_expantion(char *hd_line)
// {
// 	//to be done
// 	return (hd_line);
// }


// /* if delimiter is not quoted(has_quoted = false):
// - lines are subject to expansion;
// - \n is ignored;
// - \ for quoting characters \, $ and ` // to be check!!!
// if delimiter is quoted(has_quoted = true):
// - the text in the here-document is taken literally,*/


// void	ft_put_heredoc_line(char *hd_line, int fd_hd, bool quoted)
// {
// 	if (quoted == false)
// 		printf("Need to be no quotes rules");
// 		// ft_putendl_fd(hd_line, fd_hd);
// 	else
// 		ft_putendl_fd(hd_line, fd_hd);
// 	// int	i;

// 	// i = 0;
// 	// while (hd_line[i])
// 	// {
// 	// 	//handle here_doc expansion $ later
// 	// 	ft_putchar_fd(hd_line[i], fd_hd);
// 	// 	i++;
// 	// }
// 	// ft_putchar_fd('\n', fd_hd);
// }

// void	ft_heredoc_expander(char *hd_line, int fd_hd)
// {
// 	size_t	i;

// 	i = 0;
// 	while (hd_line[i])
// 	{
// 		// if (hd_line[i] == '\')
// 		// if next \ n $ or ' write 2d if not skip 1st??
// 		if (hd_line[i] == '$')
// 			i += ft_heredoc_expand_writer(hd_line, i, fd_hd);

// 		else
// 			i += (ft_putchar_fd(hd_line[i], fd_hd), 1);
// 	}
// 	ft_putchar_fd('\n', fd_hd);
// }

// // static int	ft_heredoc_expand_writer(char *str, size_t i, int fd)
// // {
// // 	size_t	start;
// // 	char	*tmp;

// // 	start = ++i;
// // 	if (str[i] == '?')
// // 		return (ft_putnbr_fd(g_minishell.exit_s, fd), 2);
// // 	while (str[i] && str[i] != '$' && str[i] != ' ')
// // 		i++;
// // 	if (i != start)
// // 	{
// // 		tmp = ft_garbage_collector(ft_substr(str, start, i), false);
// // 		tmp = ft_get_envlst_val(tmp);
// // 		if (tmp)
// // 			ft_putstr_fd(tmp, fd);
// // 	}
// // 	return (i);
// // }

// bool	ft_is_delimiter(char *delimiter, char *hd_line)
// {
// 	while (*hd_line)
// 	{
// 		if (*delimiter == '"' || *delimiter == '\'')
// 		{
// 			delimiter++;
// 			continue ;
// 		}
// 		else if (*hd_line == *delimiter)
// 		{
// 			hd_line++;
// 			delimiter++;
// 		}
// 		else
// 			return (false);
// 	}
// 	while (*delimiter == '"' || *delimiter == '\'')
// 		delimiter++;
// 	return (!*delimiter);
// }
