/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:30:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/10 14:31:55 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	Function creates a name for the heredoc file. 
	It will be a hidden file in the /temp
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
- If the delimiter is quoted, the text in the here-document 
is taken literally, w/o any expansions.
- If the delimiter is unquoted, the text in the here-document
 is subject to expansions.
*/

bool	ft_is_delimiter_quoted(char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == '"' || *delimiter == '\'')
			return (true);
		delimiter ++;
	}
	return (false);
}

bool	ft_is_delimiter(char *delimiter, char *hd_line)
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
