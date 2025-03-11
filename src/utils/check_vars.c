#include <minishell.h>

/*
	Minishell is not expecting any argument when programme is launched.
	Minishell is launched,
	then it provides a prompt for the user to write an input
*/
int	check_args(int ac, char **av, char **envp)
{
	(void) av;
	if (!envp || !*envp)
		ft_putendl_fd(RED "No envp: " DFLT, 2);
	if (ac > 1)
	{
		ft_putendl_fd(RED "Invalid input" DFLT, 2);
		exit(1);
	}
	return (0);
}

int	is_exact_var(t_env *env_var, const char *var_name)
{
	char	*plus;
	char	*equals_var;
	char	*equals_env;
	size_t	name_len;
	size_t	env_len;

	plus = ft_strnstr(var_name, "+=", ft_strlen(var_name));
	equals_var = ft_strchr(var_name, "=");
	equals_env = ft_strchr(env_var->key, "=");
	if (plus)
		name_len = plus - var_name;
	else if (equals_var)
		name_len = equals_var - var_name;
	else
		name_len = ft_strlen(var_name);
	if (equals_env)
		env_len = equals_var - env_var->key;
	else
		env_len = ft_strlen(env_var->key);
	if (name_len != env_len)
		return (0);
	return (ft_strncmp(env_var->key, var_name, name_len) == 0);
}
