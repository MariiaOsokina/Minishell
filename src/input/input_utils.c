#include "minishell.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	check_line_len(char *line)
{
	if (ft_strlen(line) > 200)
		return (ft_putendl_fd(LINE_ERROR, 2), false);
	return (true);
}

void	balance_message(int balance)
{
	if (balance < 0)
		ft_putendl_fd(CLOSE_ERROR, 2);
	else if (balance > 0)
		ft_putendl_fd(OPEN_ERROR, 2);
}

/*Checking for valid parenthesis*/
bool	check_parenthesis(char *str)
{
	int	i;
	int	balance;

	i = 0;
	balance = 0;
	while (str[i])
	{
		if (str[i] == ')' && balance == 0)
			return (balance_message(-1), false);
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
			balance--;
		i++;
	}
	if (balance != 0)
		balance_message(balance);
	if (balance == 0)
		return (true);
	return (false);
}
