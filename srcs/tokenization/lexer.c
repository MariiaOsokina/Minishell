/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:36:43 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/29 16:36:46 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*lexer.c*/
t_token_type	token_type(char *value)
{
	if (ft_strcmp(value, "|"))
		return (PIPE);
	else
		return (WORD);
}

/*lexer.c*/
int	check_balance(char *input, int i)
{
	int	bal;

	bal = 1;
	while (input[i] && bal != 0)
	{
		i++;
		if (input[i] && input[i] == '(')
			bal++;
		if (input[i] && input[i] == ')')
			bal--;
	}
	return (i);
}

/*lexer.c*/
void	set_token_position(t_list *lst)
{
	int		i;
	t_token	*token;

	i = 0;
	while (lst)
	{
		token = (t_token *)lst->content;
		token->pos = i;
		lst = lst->next;
		i++;
	}
}

/*Lexing starts here*/
bool	lexer(t_shell *shell, char *input)
{
	shell->token_lst = NULL;
	tokenize_input(shell, input);
	return (check_paren_types(shell));
}
