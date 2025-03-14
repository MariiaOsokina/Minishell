#include "../includes/structs.h"

void	*ft_env_lst(t_shell *shell, char **envp);
t_env	*ft_create_env_node(t_shell *shell, char *env);
void	ft_free_env_lst(t_list **envp);
void	ft_print_env_lst(t_list *lst);

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

    env_lst(&shell, envp);
	print_env_lst(shell.envp);
	free_env_lst(&shell.envp);
	return 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (ft_strncmp(s1, s2, s1_len));
	else
		return (ft_strncmp(s1, s2, s2_len));
}

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (ft_strdup(str));
}

char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_substr(str, i, ft_strlen(str) - i));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	*ft_env_lst(t_shell *shell, char **envp)
{
	int	i;

	t_env *env_content;
	shell->envp = NULL;
	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_content = create_env_node(shell, envp[i]);
		if (!env_content)
			// exit_failure(shell, "env_list");
		{
			printf("env_value\n");
			exit(1);
		}
		ft_lstadd_back(&shell->envp, ft_lstnew(env_content));
		i++;
	}
	return (NULL);
}

t_env	*ft_create_env_node(t_shell *shell, char *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		// exit_failure(shell, "create_env_node");
	{
		printf("env_value\n");
		exit(1);
	}
	if (ft_strcmp(env, "=") == 0)
	{
		node->key = ft_strdup(env);
		node->value = NULL;
	}
	else
	{
		node->key = ft_extract_key(env);
		node->value = ft_extract_value(env);		
	}
	return (node);
}

// char	*get_value(t_shell *shell, char *env, char *savedptr)
// {
// 	char	*value;
// 	char	*r_value;

// 	value = strtok_r(env, "=", &savedptr); //might change this
// 	r_value = malloc(ft_strlen(value) + 1);
// 	if (!value)
// 	{
// 		printf("env_value\n");
// 		exit(1);
// 	}
// 		// exit_failure(shell, "env_value");
// 	ft_strlcpy(r_value, value, ft_strlen(value) + 1);
// 	return (r_value);
// }

// char	*get_key(t_shell *shell, char *env, char *savedptr)
// {
// 	char	*key;
// 	char	*r_key;

// 	key = strtok_r(env, "=", &savedptr); //might change this
// 	r_key = malloc(ft_strlen(key) + 1);
// 	if (!key)
// 	{
// 		printf("key\n");
// 		exit(1);
// 	}
// 	ft_strlcpy(r_key, key, ft_strlen(key) + 1);
// 	return (r_key);
// }

void	ft_print_env_lst(t_list *lst)
{
	t_env	*env_var;

	while (lst)
	{
		env_var = (t_env *)lst->content;
		printf("%s='%s'\n", env_var->key, env_var->value);
		// if (env_var->key && ft_strchr(env_var->value, '='))
		// {
		// 	printf("%s", env_var->key);
		// 	printf("%s\n", env_var->value);
		// }
		lst = lst->next;
	}
}

void	ft_free_env_lst(t_list **envp)
{
	t_list	*tmp;
	t_env	*envp_node;

	while (*envp)
	{
		tmp = (*envp)->next;
		envp_node = (t_env *)(*envp)->content;
		if (envp_node)
		{
			if(envp_node->key)
				free(envp_node->key);
			if(envp_node->value)
				free(envp_node->value);
			free(envp_node);
		}
		free(*envp);
		*envp = tmp;
	}
	free(*envp);
	envp = NULL;
}
