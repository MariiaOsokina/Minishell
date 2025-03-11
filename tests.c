#include <stdio.h>
#include <string.h>

char	*get_key(char *env, char **svdptr)
{
	char	*key;

	key = strtok_r(env, "=", svdptr);
	return (key);
}

char	*get_value(char *env, char **svdptr)
{
	char	*value;

	value = strtok_r(NULL, "=", svdptr);
	return (value);
}

void	print_envp(char **envp)
{
	int	i;
	char	*savedptr;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i], &savedptr);
		value = get_value(envp[i], &savedptr);
		if (key && value)
			printf("key: %s :: value: %s\n", key, value);
		i++;
	}

}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	print_envp(envp);
	return (0);
}
