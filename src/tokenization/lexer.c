#include "minishell.h"

t_token_type	token_type(char *value)
{
	if (ft_strcmp(value, "|"))
		return (PIPE);
	else
		return (WORD);
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

void	set_token_position(t_list *lst)
{
	int	i;
	t_token *token;

	i = 0;
	while (lst)
	{
		token = (t_token *)lst->next;
		token->pos = i;
		lst = lst->next;
		i++;
	}
}

/*Lexing starts here*/
void	lexer(t_shell *shell, char *input)
{
	shell->token_lst = NULL;
	tokenize_input(shell, input);
}
