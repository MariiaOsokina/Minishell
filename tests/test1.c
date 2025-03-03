
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

bool	ft_is_env_key_valid(char *str);

int main(void)
{
    char *v1 = "VAR";
    char *v2 = "VAR=";

    printf("%d\n", ft_is_env_key_valid(v1));
    printf("%d\n", ft_is_env_key_valid(v2));

    return (0);
}

bool	ft_is_env_key_valid(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	if (!ft_strchr(str, '='))
        return (false);
        while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (1);
}