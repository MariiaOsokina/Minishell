#include "minishell.h"

void	print_cmd_lst(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->input[i])
	{
		printf("item: %s\n", shell->input);
		i++;
	}
}

void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("[%s]➜", (char *)lst->content);
		lst = lst->next;
	}
	printf("0\n");
}

void	token_loop(t_token *token)
{
	if (token->type == HEREDOC)
		printf("%-10s | ", "HEREDOC");
	if (token->type == OR)
		printf("%-10s | ", "OR");
	if (token->type == AND_IF)
		printf("%-10s | ", "AND_IF");
	if (token->type == PARENTHESIS)
		printf("%-10s | ", "PARNTHSIS");
	if (token->state == GENERAL)
		printf("%-12s | ", "GENERAL");
	else if (token->state == IN_DQUOTES)
		printf("%-12s | ", "IN_DQUOTES");
	else if (token->state == IN_SQUOTES)
		printf("%-12s | ", "IN_SQUOTES");
	else if (token->state == EXPAND)
		printf("%-12s | ", "EXPANSION");
}

void	print_token_lst(t_list *lst)
{
	t_token	*token;

	printf("+---------------+------------+--------------+----------+\n");
	printf("|    value      |    Type    |    State     | Psition  |\n");
	printf("+---------------+------------+--------------+----------+\n");
	while (lst)
	{
		token = (t_token *)lst->content;
		printf("| %-13s | ", token->value);
		if (token->type == WORD)
			printf("%-10s | ", "WORD");
		else if (token->type == PIPE)
			printf("%-10s | ", "PIPE");
		else if (token->type == APPEND)
			printf("%-10s | ", "APPEND");
		else if (token->type == OUTFILE)
			printf("%-10s | ", "OUTFILE");
		else if (token->type == INFILE)
			printf("%-10s | ", "INFILE");
		token_loop(token);
		printf("-6 |\n", token->pos);
		lst = lst->next;
	}
	printf("+---------------+------------+--------------+----------+\n");
}
