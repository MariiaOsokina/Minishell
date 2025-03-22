#include "minishell.h"

char	*ft_strjoin_char(char *str, char c)
{
	int		i;
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	free(str);
	return (new_str);
}

int	join_strs(t_shell *shell, char **str, char *input, int i)
{
	if (is_quote(input[i]))
		i = hndl_quoted_str(shell, str, input, i);
	else
		i = hndl_nonquoted_str(shell, str, input, i);
	return (i);
}

int	check_escapes(char *input, int start, int i, char quote)
{
	int	j;
	int	backslashes;

	while (input[i])
	{
		if (input[i] == quote)
		{
			j = i - 1;
			backslashes = 0;
			while (j >= start + 1 && input[j] == '\\')
			{
				backslashes++;
				j--;
			}
			if (backslashes % 2 == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_flag(char c, int *i, bool flag)
{
	if (c == '"')
	{
		*i = *i + 1;
		return (!flag);
	}
	return (flag);
}

t_token	*create_token(t_shell *shell, char *str)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "create_token");
	new_token->value = str;
	new_token->type = WORD;
	new_token->state = GENERAL;
	if (!ft_strcmp(str, ""))
		new_token->state = EXPAND;
	return (new_token);
}
