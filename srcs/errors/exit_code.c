#include "minishell.h"

int	exit_code(t_shell *shell, int value)
{
	shell->exit_code = value;
	return (shell->exit_code);
}

char	*itoa_exit(t_shell *shell, char **str)
{
	char	*tmp;
	char	*code;

	code = ft_itoa(exit_code(shell, shell->exit_code));
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

