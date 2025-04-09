/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:00:44 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/09 14:58:14 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
if delimiter is not quoted(has_quoted = false):
- lines are subject to expansion;
- \n is ignored;
- \ for quoting characters \, $ and ` // to be check!!!
*/

char *ft_hd_line_expansion(char *hd_line)
{
	//to be done
	return (hd_line);
}

static bool	ft_is_double_cbraces(char *str)
{
	int i;
	bool doubled;

	i = 0;
	doubled = false;
	if (str[i] == '{') // Handle ${VAR}
	{
		while(str[i])
		{
			if (str[i] == "}")
				doubled == true;
			i ++;
		}
	}
	return (doubled);
}

static void	ft_handle_cbraces(char *str, size_t *i, size_t *start, char **var)
{
		if (str[*(i)] == '{') // Handle ${VAR}
		{
			if (ft_is_double_cbraces(str) == false)
			{
				ft_err_msg("should be hd_line", "bad substitution", NULL);
			}
			*(i)++; // skip '{'
			*start = *i;
			while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
				*i++;
			if (str[*i] != '}') // invalid syntax, skip
				return (0);
			*var = ft_substr(str, start, *i - *start);
			*(i)++; // skip '}'	
		}
}

static int	ft_heredoc_env_expand(t_shell *shell, char *str, size_t i, int fd)
{
	size_t	start;
	t_env	*tmp_env;
	char	*var;

	i += 1;
	start = i;
	var = NULL;
	ft_handle_cbraces(str, &i, &start, &var);
	if (str[i] == '?')
		return (ft_putnbr_fd(shell->exit_code, fd), 2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i != start)
		var = ft_substr(str, start, i -start);
	if (var)
	{
		tmp_env = ft_get_env_node(*shell, var);
		free(var);
		if (tmp_env && tmp_env->value)
			ft_putstr_fd(tmp_env->value, fd);
	}
	return (i - start + 1);
}

void	ft_heredoc_unquoted(t_shell *shell, char *hd_line, int hd_fd)
{
	int	i;

	i = 0;
	while (hd_line[i])
	{
		// if (hd_line[i] == '\')
		// 	i ++;
		// if next \ n $ or ' write 2d if not skip 1st??
		if (hd_line[i] == '$')
		{
			i += ft_heredoc_env_expand(shell, hd_line, i, hd_fd);
		}

		else
			i += (ft_putchar_fd(hd_line[i], hd_fd), 1);
	}
	ft_putchar_fd('\n', hd_fd);
}
