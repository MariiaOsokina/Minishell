#include "minishell.h"

/*
	This function (env_lst) creates a linked list in the shell struct
	containing the envp parameters passed from the command line
	which can be used and available for execution when required.
	Hence, we will not require passing envp as a parameter to functions
	that needs to execute a command as it is alreay available in the shell struct.
*/
void	*env_lst(t_shell *shell, char **envp)
{
	int	i;
	t_env	*content; //content->content//key && content->value//value..

	shell->envp = NULL;
	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		content = create_env_node(shell, &envp[i]);
		if (!content)
			exit_failure(shell, "env_list");
		ft_lstadd_back(&shell->envp, ft_lstnew(content));
		i++;
	}
	return (NULL);
}

t_env	*create_env_node(t_shell *shell, char **envp)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_failure(shell, "create_env_node");
	node->value = get_value(shell, *envp);
	node->content = get_content(shell, *envp);
	node->is_export = true;
	node->is_printed = false;
	return (node);
}

char	*get_value(t_shell *shell, char *env)
{
	char	*value;

	value = malloc(sizeof(char) * value_size(env) + 1);
	if (!value)
		exit_failure(shell, "env_value");
	ft_strlcpy(value, env, value_size(env) + 1);
	return (value);
}

char	*get_content(t_shell *shell, char *env)
{
	char	*content;

	content = malloc(sizeof(char) * content_size(env) + 1);
	if (!content)
		exit_failure(shell, "env_content");
	ft_strlcpy(content, env, ft_strlen(env));
	return (content);
}

/* This function searches the env list in shell struct and the returns the value*/
// char	*sh_get_env(t_list *envp, const char *value) // MO : should be key
// {
// 	t_list	*current;
// 	t_env	*env_entry;

// 	current = envp;
// 	while (current)
// 	{
// 		env_entry = (t_env *)current->content;
// 		if (is_exact_var(env_entry, value)) //MO: ft_strcmp we can use here!!!
// 			return (env_entry->content);
// 		current = current->next;
// 	}
// 	return (NULL);
// }


//MO's version
char	*sh_get_env(t_list *envp, const char *key) // MO : should be key
{
	t_list	*current;
	t_env	*env_entry;

	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (!ft_strcmp(env_entry, key)) //MO: ft_strcmp we can use here!!!
			return (env_entry->value); //not content, should be value;
		current = current->next;
	}
	return (NULL);
}
