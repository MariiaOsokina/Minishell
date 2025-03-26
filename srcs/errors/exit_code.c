#include "minishell.h"

int	exit_code(int value)
{
	static int	code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}

char	*itoa_exit(t_shell *shell, char **str)
{
	char	*tmp;
	char	*code;

	code = ft_itoa(exit_code(-1));
	if (!code)
		exit_failure(shell, "itoa_exit");
	tmp = *str;
	*str = ft_strjoin(*str, code);
	free(tmp);
	free(code);
	if (!*str)
		exit_failure(shell, "itoa_exits");
	return (*str);
}
