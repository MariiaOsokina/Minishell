#include "minishell.h"

int	expand_single(t_shell *shell, char **str, char *input, int i)
{
	int	start;
	char	*tmp;
	char	*subs;

	while (input[i] && input[i] != '\'')
		i++;
	subs = ft_substr(input, start, i - start);
	if (!subs)
		exit_failure(shell, "expand_single");
	tmp = *str;
	*str = ft_strjoin(*str, subs);
	if (!subs)
		exit_failure(shell, "expand_single");
	free(tmp);
	free(subs);
	return (++i);
}

int	expand_quoted(t_shell *shell, char **str, char *input, int i)
{
	int	start;
	char	*tmp;
	char	*var_name;
	char	*var_value;

	start = ++i;
	while (input[i] && !is_space(input[i]) && \
			(ft_isalnum(input[i]) || input[i] == '_') \
			&& input[i] != '"')
			i++;
	if (input[i] == '?')
		return (*str = itoa_exit(shell, str), ++i);
	var_name = ft_substr(input, start, i - start);
	if (!var_name)
		exit_failure(shell, "expand_quoted");
	var_value = getenv(var_name);
	free(var_name);
	if (var_value)
	{
		tmp = *str;
		*str = ft_strjoin(*str, var_value);
		free(tmp);
	}
	return (i);
}

int	expand_unquoted(t_shell *shell, char **str, char *input, int i)
{
	const char	start = ++i;
	char	*tmp;
	char	*var_name;
	char	*var_value;

	while (input[i] && !is_space(input[i]) && \
			(ft_isalnum(input[i]) || input[i] == '_') && \
			!is_meta(input, i))
			i++;
	if (input[i] == '?')
		return (*str = itoa_exit(shell, str), ++i);
	var_name = ft_substr(input, start, i - start);
	if (!var_name)
		exit_failure(shell, "expand_unquoted");
	var_value = sh_get_env(shell->envp, var_name);
	free(var_name);
	if (var_value)
	{
		tmp = *str;
		*str = ft_strjoin(*str, var_value);
		free(tmp);
	}
	return (i);
}

int	process_expansion(t_shell *shell, char **str, char *input, int i)
{
	int	flag;

	flag = 0;
	while (input[i] && !is_space(input[i]) && !is_meta(input, i))
	{
		while (input[i] == '$')
			i = expand_unquoted(shell, str, input, i);
		flag = ft_flag(input[i], &i, flag);
		while (input[i] && flag)
		{
			while (input[i] && input[i] != '$' && input[i] != '"')
				*str = ft_strjoin_char(*str, input[i++]);
			if (input[i] == '$' || input[i] == '"')
				i = expand_quoted(shell, str, input, i);
			flag = ft_flag(input[i], &i, flag);
		}
		if (input[i] && input[i] == '\'')
			i = expand_single(shell, str, input, i);
		else if (input[i] && !is_meta(input, i) && !is_space(input[i]))
			*str = ft_strjoin_char(*str, input[i++]);
	}
	return (i);
}

char	*handle_expansion(t_shell *shell, char *input, int i)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		exit_failure(shell, "handle_expansion");
	while (input[i])
	{
		if (input[i] == '$' || is_quote(input[i]))
			i = process_expansion(shell, &str, input, i);
		else
			while (input[i] && (input[i] != '$' && input[i] != '"'))
				str = ft_strjoin_char(str, input[i++]);
		if (is_space(input[i]) || is_meta(input, i))
			break ;
	}
	if (ft_strlen(str) == 0 && input[0] == '$')
	{
		free(str);
		return (NULL);
	}
	return (str);
}
