/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:53:16 by aaladeok          #+#    #+#             */
/*   Updated: 2025/05/06 09:53:36 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token_error_message(t_shell *shell, t_list *token)
{
	ft_putstr_fd(SYNTAX_ERROR TOKEN_ERROR, 2);
	if (((t_token *)token->content)->value[0] == '(')
		ft_putendl_fd("('", 2);
	else
	{
		ft_putstr_fd(((t_token *)token->content)->value, 2);
		ft_putendl_fd("'", 2);
	}
	free_shell(shell);
	ft_lstclear(&shell->token_lst, del_token);
	return ;
}

bool	check_paren_types(t_shell *shell)
{
	t_list	*temp;
	t_token	*token;

	temp = shell->token_lst;
	while (temp)
	{
		token = (t_token *)(temp)->content;
		if ((token->type == PARENTHESIS && token->value[0] == ')'
				&& token->value[1] == '\0' && temp->next
				&& ((t_token *)temp->next->content)->type == WORD)
			|| (token->type == WORD && temp->next
				&& ((t_token *)temp->next->content)->type == PARENTHESIS
				&& ((t_token *)temp->next->content)->value[0] == '(')
			|| ((token->type == AND_IF || token->type == OR) && temp->next
				&& is_operator(temp->next)))
		{
			print_token_error_message(shell, temp->next);
			return (exit_code(shell, 2), false);
		}
		temp = temp->next;
	}
	return (true);
}

// && ((t_token *)temp->next->content)->type == AND_IF || 
// ((t_token *)temp->next->content)->type == AND_IF))