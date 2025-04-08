/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:25:38 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/08 13:31:06 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO BE SOLVED: 
1 - update env_arr, envp, cwd ??? three places with the same values;
2 - SHOULD BE HANDLED? 
If path(2nd arg) is “-”, it should be previous dir
seach OLDPWD path in the list of env variables,passed 
in the beginning of the program (shell.envp)
If no OLDPWD in envp, error “OLDPWD not set” with exit code 1 
(e.g. in case if unset OLDPWD)
3 - ??In env update functions we need to think about 
garbage collector(clear old node);
4 - //in progress, needs to be tested

*/

/* STEPS:
1 - NOTES: No options in the Minishell Subject! 
So, “--” and "-" should be treated as an option;

2 - If more than two args, error “too many arguments” with exit code 1 
(but NOT exit from the process!!!)

3 - If no path(2nd arg), it should be home dir
	- seach HOME path in the list of env variables, passed 
	in the beginning of the program (shell.envp)
	- if no HOME in envp, error “HOME not set” 
	with exit code 1 (e.g. in case if unset HOME);

4 - Change dir with function chdir(form unistd.h)
	- If chdir returns error, error “No such file or directory” with exit code 1 

5 - Update list of env (shell.envp);
 - if $PWD was unset, add new env node to envp, 
 else update value PWD, value is getcwd())
*/

static void	ft_update_pwd_env(t_shell *shell, char *new_dir)
{
	t_env	*new_pwd_env;

	new_pwd_env = NULL;
	if (ft_get_env_node(*shell, "PWD") != NULL)
		ft_update_env_value(shell->envp, "PWD", new_dir);
	else
	{
		new_pwd_env = ft_dup_env_node(shell, "PWD", new_dir);
		ft_lstadd_back(&shell->envp, ft_lstnew(new_pwd_env));
	}
}

static void	ft_update_oldpwd_env(t_shell *shell, char *old_dir)
{
	t_env	*new_oldpwd_env;

	new_oldpwd_env = NULL;
	if (ft_get_env_node(*shell, "OLDPWD") != NULL)
		ft_update_env_value(shell->envp, "OLDPWD", old_dir);
	else
	{
		new_oldpwd_env = ft_dup_env_node(shell, "OLDPWD", old_dir);
		ft_lstadd_back(&shell->envp, ft_lstnew(new_oldpwd_env));
	}
}

static int	ft_change_dir(t_shell *shell, char *path)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (chdir(path) != ENO_SUCCESS)
	{
		free(old_dir);
		ft_err_msg("cd", path, "No such file or directory");
		return (ENO_GENERAL);
	}
	new_dir = getcwd(NULL, 0);
	ft_update_pwd_env(shell, new_dir);
	ft_update_oldpwd_env(shell, old_dir);
	if (old_dir)
		free(old_dir);
	if (new_dir)
		free(new_dir);
	return (ENO_SUCCESS);
}

int	ft_builtin_cd(t_shell *shell, t_exec *exec_node)
{
	char	*path;
	t_env	*home_env;

	path = exec_node->av[1];
	home_env = NULL;
	if (ft_arr_size(exec_node->av) > 2)
		return (ft_err_msg("cd", "too many arguments", NULL), ENO_GENERAL);
	else if (!path)
	{
		home_env = ft_get_env_node(*shell, "HOME");
		if (!home_env)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
		else
			path = home_env->value;
	}
	return (ft_change_dir(shell, path));
}
