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


bool	check_paren_types(t_shell *shell)
{
	t_list	*temp;
	t_token	*token;

	temp = shell->token_lst;

	while (temp)
	{
		token = (t_token *)(temp)->content;
		if (token->type == PARENTHESIS && token->value[0] == ')' && token->value[1] == '\0')
		{
			if (temp->next &&( ((t_token *)temp->next->content)->type == WORD || ((t_token *)temp->next->content)->value[0] == '('))
			{
				ft_putendl_fd(SYNTAX_ERROR OPEN_ERROR, 2);
				ft_lstclear(&shell->token_lst, del_token);
				free_shell(shell);
				return (exit_code(shell, 2), false);
			}
		}
		temp = temp->next;
	}
	return (true);
}

/*Lexing starts here*/
bool	lexer(t_shell *shell, char *input)
{
	shell->token_lst = NULL;
	tokenize_input(shell, input);
	return (check_paren_types(shell));
}
