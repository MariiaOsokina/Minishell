#include "minishell.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	check_line_len(char *line)
{
	if (ft_strlen(line) > 400)
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

bool	handle_paren(char c, int *bal)
{
	if (c == '(')
		(*bal)++;
	else if (c == ')')
	{
		if (*bal == 0)
			return (false);
		(*bal)--;
	}
	return (true);
}

//Bare parenthesis checks, no types!!
bool	check_empty_parens(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' && str[i + 1] == ')')
			return (true);
		if (str[i] == ')')
		{
			if (i > 0 && str[i - 1] == '(')
				return (true);
			if (str[i + 1] == '(')
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_parenthesis(char *str)
{
	int	i;
	int	bal;
	bool	sq;
	bool	dq;

	i = 0;
	bal = 0;
	sq = false;
	dq = false;

	if (check_empty_parens(str))
		return (ft_putendl_fd(SYNTAX_ERROR CLOSE_ERROR, 2), (false));
	while (str[i])
	{
		toggle_quotes(str[i], &sq, &dq);
		if (!sq && !dq && !handle_paren(str[i], &bal))
			return (balance_message(-1), false);
		i++;
	}
	if (sq || dq)
		return (ft_putendl_fd(OPEN_QUOTE, 2), false);
	if (bal != 0)
		return (balance_message(bal), false);
	return (true);
}

/*Checking for valid parenthesis old version
// bool	check_parenthesis(char *str)
// {
// 	int		i;
// 	int		balance;

// 	i = 0;
// 	balance = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ')' && balance == 0)
// 			return (balance_message(-1), false);
// 		if (str[i] == '(')
// 			balance++;
// 		else if (str[i] == ')')
// 			balance--;
// 		i++;
// 	}
// 	if (balance != 0)
// 		balance_message(balance);
// 	if (balance == 0)
// 		return (true);
// 	return (false);
// }
*/


//Problems to address
//(/bin/echo 1) (/bin/echo 2) subshell after subshell.
//() empty subshell
