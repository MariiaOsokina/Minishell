/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:00:51 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/07 12:14:22 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*TO BE SOLVED: 
1 - update env_arr, envp, cwd ??? three places with the same values;
2 - SHOULD BE HANDLED? 
If path(2nd arg) is “-”, it should be previous dir
seach OLDPWD path in the list of env variables,passed in the beginning of the program (shell.envp)
If no OLDPWD in envp, error “OLDPWD not set” with exit code 1 (e.g. in case if unset OLDPWD)
3 - ??In env update functions we need to think about garbage collector(clear old node);
4 - //in progress, needs to be tested

*/

/*
1 - NOTES: No options in the Minishell Subject! So, “--” and "-" should be treated as an option;

2 - If more than two args, error “too many arguments” with exit code 1 (but not exit from the process!!!)

3 - If no path(2nd arg), it should be home dir
	- seach HOME path in the list of env variables, passed in the beginning of the program (shell.envp)
	- if no HOME in envp, error “HOME not set” with exit code 1 (e.g. in case if unset HOME);

4 - Change dir with chdir(form unistd.h)
	- If chdir returns error, error “No such file or directory” with exit code 1 (e.g. in case…)

5 - Update list of env (shell.envp): //updated shell.env_arr, shell.cwd??
- OLDPWD should be equal to PWD //check case if no $OLDPWD??
- PWD should be equal to getcwd()  //check case if no $PWD??
*/


static int ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i ++;
	return (i);
}

char	*ft_get_env_value(t_list *envp, const char *key)
{
	t_list	*current_list;
	t_env	*env_content;

	current_list = envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, key)) // think about function from ade is_var!!!
			return (env_content->value);
        current_list = current_list->next;
	}
	return (NULL);
}


int	builtin_cd(t_shell shell, t_node *cmd)
{
	char *path;

	path = cmd->expanded_args[1];
	if (ft_arr_size (cmd->expanded_args) > 2) //arr should be with null terminator
	{
		return (ft_err_msg("cd", "too many arguments", NULL), ENO_GENERAL);
	}
	else if (!path)
	{
		path = ft_get_env_value(shell.envp, "HOME");
		if (!path)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
	}
	// else if (ft_strcmp (path, "-") == 0)
	// {
	// 	path = ft_get_env_value("OLDPWD");
	// 	if (!path)
	// 		return (ft_err_msg("cd", "OLDPWD not set", NULL), ENO_GENERAL);
	// 	ft_printf("%s\n", path);
	// }
	if (chdir(path) != ENO_SUCCESS)
		return (ft_err_msg("cd", path, "No such file or directory"), ENO_GENERAL);
	//check if unset OLDPWD // ft_add_envlist
	ft_update_env_value(shell.envp, "OLDPWD", ft_get_env_value(shell.envp, "PWD"));
	//check if unset PWD // ft_add_envlist
	ft_update_env_value(shell.envp, "PWD", getcwd(NULL, 0));
    return (ENO_SUCCESS);
}

// void	set_pwdenv(char *dir, int flag)
// {
// 	char	dir2[LINE_MAX];
// 	t_env	*old;
// 	t_env	*pwd;

// 	pwd = ret_env("PWD");
// 	old = ret_env("OLDPWD");
// 	if (!old)
// 	{
// 		set_var("OLDPWD", '=', NULL, 0);
// 		old = ret_env("OLDPWD");
// 	}
// 	if (pwd)
// 		old->value = pwd->value;
// 	else
// 	{
// 		old->value = ft_strdup(dir);
// 		set_var("PWD", '=', NULL, 0);
// 		pwd = ret_env("PWD");
// 	}
// 	if (!getcwd(dir2, LINE_MAX))
// 		pwd->value = ft_strdup(pwd->value);
// 	else
// 		pwd->value = ft_strdup(dir2);
// 	if (flag == 1)
// 		pwd->value = cat_value(pwd->value, 0, "/.");
// }