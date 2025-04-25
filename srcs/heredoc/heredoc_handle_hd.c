/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle_hd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:26:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 19:41:41 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NOTE: 
- If the delimiter is quoted, the text in the here-document 
is taken literally, w/o any expansions.
- If the delimiter is unquoted, the text in the here-document
 is subject to expansions.
*/

static bool	ft_is_delimiter_quoted(char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == '"' || *delimiter == '\'')
			return (true);
		delimiter ++;
	}
	return (false);
}

static void	ft_fill_heredoc(t_shell *shell, t_in_out *io_here)
{
	bool	has_quoted;
	int		hd_fd;

	has_quoted = ft_is_delimiter_quoted(io_here->eof);
	hd_fd = open(io_here->name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	ft_signals_heredoc();
	ft_heredoc_input(shell, io_here, hd_fd, has_quoted);
	close(hd_fd);
	ft_signals_interactive();
}

/* 
	Function creates a name for the heredoc file. 
	It will be a hidden file in the /temp
	folder. The static variable guarantees to have successive numbers.
 */

static char	*ft_generate_heredoc_name(void)
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

void	ft_handle_heredocs(t_shell *shell, t_exec *exec_node)
{
	t_list		*current;
	t_in_out	*io_node;
	char		*hd_arr_name;

	current = exec_node->i_ofiles;
	while (current && g_signum != SIGINT)
	{
		io_node = (t_in_out *)current->content;
		if (io_node->type == HERE)
		{
			hd_arr_name = ft_generate_heredoc_name();
			ft_lstadd_back(&(shell->heredoc_names), ft_lstnew(hd_arr_name));
			io_node->name = ft_strdup(hd_arr_name);
			ft_fill_heredoc(shell, io_node);
		}
		current = current->next;
	}
	return ;
}

void	ft_unlink_heredocs(t_list *heredoc_names)
{
	if (heredoc_names == NULL)
		return ;
	while (heredoc_names)
	{
		if ((heredoc_names)->content)
		{
			if (unlink((char *)(heredoc_names)->content) != 0)
				ft_putstr_fd("unlink error\n", STDERR_FILENO);
		}
		heredoc_names = (heredoc_names)->next;
	}
}
