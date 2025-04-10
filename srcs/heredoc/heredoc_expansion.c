/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:00:44 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/09 19:53:55 by mosokina         ###   ########.fr       */
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

static bool	ft_is_valid_substitution(char *str)
{
	int i = 0;

	i += 2; // skip past '${'

	// Empty content inside ${}
	if (str[i] == '}')
		return false;
	// Check if it's a valid variable name or acceptable Bash expression
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		// Now allow bash constructs like :-, :=, //, ^^ etc. optionally
		// e.g. ${VAR:-default}, ${VAR//a/b}
		while (str[i] && str[i] != '}')
			i++;
	}
	else
	{
		// invalid start inside ${}
		return false;
	}
	if (str[i] != '}')
		return false;
	return true;
}

static void	ft_handle_cbraces(char *str, size_t *i, size_t *start, char **var)
{

		*i += 2; // skip '${'
		*start = *i;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		*var = ft_substr(str, *start, *i - *start);
		if (str[*i] == '}')
			(*i)++; // skip '}'
	}
}


static int	ft_heredoc_env_expand(t_shell *shell, char *str, size_t i, int fd)
{
	size_t	start;
	t_env	*tmp_env;
	char	*var;

	if (str[i] == '$' && str[i + 1] == '{')
	{
		if (!ft_is_valid_substitution(str + *i))
		{
			if (!ft_is_valid_substitution(str + *i))
			{
				ft_err_msg("should be hd_line", "bad substitution", NULL);
				return ;
			}
		}

	i += 1;
	start = i;
	var = NULL;
	ft_handle_cbraces(str, &i, &start, &var);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i != start)
		var = ft_substr(str, start, i -start);
	if (ft_strcmp(var, "?"))
		ft_putnbr_fd(shell->exit_code, fd);
	else if (var)
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
