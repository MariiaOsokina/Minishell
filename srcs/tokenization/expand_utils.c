/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:35:31 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/29 16:36:06 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_quotes(char *input, int i)
{
	if (input[i] == '"')
		return (true);
	return (false);
}

bool	is_meta(char *str, int i)
{
	int		j;
	char	*metachars;

	metachars = "<|>();&";
	j = 0;
	if (!str || i < 0)
		return (false);
	while (metachars[j] && str[i])
	{
		if (str[i] && str[i] == metachars[j])
			return (true);
		j++;
	}
	return (false);
}

int	set_append(t_shell *sh, t_token *nw_tkn, char *input, int i)
{
	nw_tkn->value = ft_strndup(&input[i], 2);
	if (!nw_tkn->value)
		exit_failure(sh, "handle_redirection_1");
	nw_tkn->type = APPEND;
	return (i + 2);
}

int	set_simple(t_shell *sh, t_token *nw_tkn, char *input, int i)
{
	nw_tkn->value = ft_strndup(&input[i], 1);
	if (!nw_tkn->value)
		exit_failure(sh, "handle_redirection_1");
	if (input[i] == '<')
		nw_tkn->type = INFILE;
	else
		nw_tkn->type = OUTFILE;
	return (i + 1);
}

void	del_token(void *token_node)
{
	t_token	*token;

	token = (t_token *)token_node;
	if (token)
	{
		free(token->value);
		free(token);
	}
}
