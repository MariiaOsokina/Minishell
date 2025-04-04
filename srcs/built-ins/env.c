#include "minishell.h"

/*This is called by the terminal to prep env variables*/
// char	**env_arr(t_shell *shell)
// {
// 	t_list	*envp_list;
// 	char	**env_arr;
// 	int		i;

// 	envp_list = shell->envp;
// 	i = ft_lstsize(envp_list);
// 	env_arr = malloc(sizeof(char *) * (i + 1));
// 	if (!env_arr)
// 		exit_failure(shell, "env_arr");
// 	i = 0;
// 	while (envp_list)
// 	{
// 		env_arr[i] = ft_strjoin(((t_env *)envp_list->content)->key,
// 				((t_env *)envp_list->content)->value);
// 		if (!env_arr[i])
// 			exit_failure(shell, "env_arr_1");
// 		envp_list = envp_list->next;
// 		i++;
// 	}
// 	env_arr[i] = NULL;
// 	return (env_arr);
// }


/*This is called by the terminal to prep env variables*/
static int count_valid_env_entries(t_list *envp_list)
{
    int count;
    t_env *env_content;

    count = 0;
    while (envp_list)
    {
        env_content = (t_env *)envp_list->content;
        if (env_content && env_content->value != NULL)
            count++;
        envp_list = envp_list->next;
    }
    return (count);
}

static char *create_env_string(t_env *env_content)
{
    char *key_with_equals;
    char *full_string;

    if (!env_content->key)
        return (NULL);
    key_with_equals = ft_strjoin(env_content->key, "=");
    if (!key_with_equals)
        return (NULL);
    full_string = ft_strjoin(key_with_equals, env_content->value);
    free(key_with_equals);
    if (!full_string)
        return (NULL);
    return (full_string);
}

// Helper function to clean up allocated memory on error
void ft_free_str_arr(char **arr, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char	**ft_env_arr(t_shell *shell)
{
    t_list *envp_list;
    char **env_arr;
    int count;
    int i;
    t_env *env_content;
    char *env_string;

    envp_list = shell->envp;
    count = count_valid_env_entries(envp_list);
    env_arr = malloc(sizeof(char *) * (count + 1));
    if (!env_arr)
        exit_failure(shell, "env_arr");
    i = 0;
    while (envp_list && i < count)
    {
        env_content = (t_env *)envp_list->content;
        if (env_content && env_content->value != NULL)
        {
            env_string = create_env_string(env_content);
            if (!env_string)
            {
                ft_free_str_arr(env_arr, i);
                exit_failure(shell, "env_arr_string");
            }
            env_arr[i++] = env_string;
        }
        envp_list = envp_list->next;
    }
    env_arr[i] = NULL;
    return (env_arr);
}

t_list	*ft_path_list(t_shell *shell)
{
	t_list	*path_list;
    t_env   *path_env;
	char	*path;
	int		i;

	path_list = NULL;
    path_env = ft_get_env(*shell, "PATH");
    if (!path_env)
        return (NULL);
    path = path_env->value;
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
		i = ft_get_path(shell, &path_list, path, i);
	return (path_list);
}

int	ft_get_path(t_shell *shell, t_list **path_list, char *path, int i)
{
	char	*new_path;
	int		start;

	start = i;
	while (path[i] && path[i] != ':')
		i++;
	new_path = ft_substr(path, start, i - start);
	if (!new_path)
    {
        // if (path)
        //     free(path);
        exit_failure(shell, "get_path");
    }
	ft_lstadd_back(path_list, ft_lstnew(new_path));
	if (path[i] == ':')
		i++;
	return (i);
}

// t_list	*path_list(t_shell *shell, char **envp)
// {
// 	t_list	*path_list;
// 	char	*path;
// 	int		i;

// 	(void)envp;
// 	path_list = NULL;
// 	path = sh_get_env(shell->envp, "PATH");
// 	// printf("path: %s\n", path);
// 	// path = sh_get_env(envp, "PATH");

// 	if (path == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (path[i])
// 		i = get_path(shell, &path_list, path, i);
// 	return (path_list);
// }



// char	*sh_get_env(t_list *envp, const char *key)
// {
// 	t_list	*current;
// 	t_env	*env_entry;

// 	current = envp;
// 	while (current)
// 	{
// 		env_entry = (t_env *)current->content;
// 		if (is_exact_var(env_entry, key)) //This helper is_exact_var();
// 			return (env_entry->value);
// 		current = current->next;
// 	}
// 	return (NULL);
// }


// int	get_path(t_shell *shell, t_list **path_list, char *path, int i)
// {
// 	char	*new_path;
// 	int		start;

// 	start = i;
// 	while (path[i] && path[i] != ':')
// 		i++;
// 	new_path = ft_substr(path, start, i - start);
// 	if (!new_path)
// 		exit_failure(shell, "get_path");
// 	ft_lstadd_back(path_list, ft_lstnew(new_path));
// 	if (path[i] == ':')
// 		i++;
// 	return (i);
// }

// void	print_env_lst(t_list *lst)
// {
// 	t_env	*env_var;

// 	while (lst)
// 	{
// 		env_var = (t_env *)lst->content;
// 		if (env_var->value && ft_strchr(env_var->key, '='))
// 		{
// 			printf("%s", env_var->key);
// 			printf("%s\n", env_var->value);
// 		}
// 		lst = lst->next;
// 	}
// }

// void	free_env_lst(t_list *envp)
// {
// 	t_list	*tmp;
// 	t_env	*envp_node;

// 	while (envp)
// 	{
// 		tmp = envp->next;
// 		envp_node = (t_env *)envp->content;
// 		if (envp_node)
// 		{
// 			free(envp_node->value);
// 			free(envp_node->key);
// 			free(envp_node);
// 		}
// 		free(envp);
// 		envp = tmp;
// 	}
// }
