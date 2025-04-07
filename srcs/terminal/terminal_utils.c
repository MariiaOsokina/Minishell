#include "minishell.h"

/*
	This function concatenates a series of textual info and
	saves it in the shell cwd which is display in by the shell prompt.
	The shell prompt displays the texts concatenated in this function.
*/
void	shell_input(t_shell *shell)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;
	char	*code;
	char	*prompt;

	code = ft_itoa(exit_code(shell->exit_code)); //MO: changed to shell.exit_code
	cwd = getcwd(NULL, 0);
	prompt = ESC_START PROMPT ESC_RESET;
	tmp = ft_strjoin(prompt, code);
	free(code);
	if (!tmp)
		exit_failure(shell, "shell_input");
	tmp2 = ft_strjoin(tmp, ESC_CODE);
	free(tmp);
	if (!tmp2)
		exit_failure(shell, "shell_input");
	tmp = ft_strjoin(tmp2, cwd);
	free(tmp2);
	if (!tmp)
		exit_failure(shell, "shell_input");
	shell->cwd = ft_strjoin(tmp, ARROW);
	free(cwd);
	free(tmp);
}
