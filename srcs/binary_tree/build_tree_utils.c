/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:12 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/29 18:46:14 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*next_token(t_list **current)
{
	if (current && *current)
		*current = (*current)->next;
	return (*current);
}

int	is_operator(t_list *token)
{
	if (!token || !token->content)
		return (0);
	return (((t_token *)token->content)->type == PIPE
		|| ((t_token *)token->content)->type == AND_IF
		|| ((t_token *)token->content)->type == OR);
}

int	is_redirection(t_list *token)
{
	if (!token || !token->content)
		return (0);
	return (((t_token *)token->content)->type == APPEND
		|| ((t_token *)token->content)->type == OUTFILE
		|| ((t_token *)token->content)->type == INFILE
		|| ((t_token *)token->content)->type == HEREDOC);
}

void	past_parenthesis(t_list **curr)
{
	while (*curr && ((t_token *)(*curr)->content)->type == PARENTHESIS)
		next_token(curr);
}

