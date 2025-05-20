/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:40:58 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/29 18:52:10 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*parse_factor(t_shell *shell, t_list **curr, bool in_subshell)
{
	void	*node;
	t_token	*tmp;
	t_op	*subshell_node;

	if (!(*curr) || !(*curr)->content)
		return (NULL);
	tmp = (t_token *)(*curr)->content;
	if (tmp->type == PARENTHESIS && ft_strcmp(tmp->value, "(") == 0)
	{
		next_token(curr);
		node = parse_expression(shell, curr, true);
		if (!node)
			return (NULL);
		next_token(curr);
		if (!in_subshell)
		{
			subshell_node = malloc(sizeof(t_op));
			subshell_node->left = node;
			subshell_node->right = NULL;
			subshell_node->type.type = N_SUBSHELL;
			return (subshell_node);
		}
		return (node);
	}
	return (create_exec_node(shell, curr));
}

void	*parse_term(t_shell *shell, t_list **curr, bool in_subshell)
{
	void	*left;
	t_pipe	*node;

	left = parse_factor(shell, curr, in_subshell);
	if (!left)
		return (NULL);
	while (*curr && (((t_token *)(*curr)->content)->type == PIPE))
	{
		node = malloc(sizeof(t_pipe));
		if (!node)
			return (NULL);
		node->type.type = N_PIPE;
		node->left = left;
		next_token(curr);
		node->right = parse_factor(shell, curr, in_subshell);
		if (!node->right)
		{
			free_ast_node(node);
			return (NULL);
		}
		left = node;
	}
	return (left);
}

void	*parse_expression(t_shell *shell, t_list **curr, bool in_subshell)
{
	void	*left;
	t_op	*node;

	left = parse_term(shell, curr, in_subshell);
	while (*curr && ((((t_token *)(*curr)->content)->type == OR)
		|| (((t_token *)(*curr)->content)->type == AND_IF)))
	{
		node = malloc(sizeof(t_op));
		if (!node)
			return (NULL);
		if (((t_token *)(*curr)->content)->type == OR)
			node->type.type = N_OR;
		else
			node->type.type = N_ANDIF;
		node->left = left;
		next_token(curr);
		node->right = parse_term(shell, curr, in_subshell);
		if (!node->right)
		{
			free_ast_node(node);
			return (NULL);
		}
		left = node;
	}
	return (left);
}

void	*build_ast(t_shell *shell)
{
	t_list	*curr;

	curr = shell->token_lst;
	return (parse_expression(shell, &curr, false));
}
