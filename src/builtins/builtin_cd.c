/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:00:51 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:04 by mosokina         ###   ########.fr       */
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

/* STEPS:
1 - NOTES: No options in the Minishell Subject! So, “--” and "-" should be treated as an option;

2 - If more than two args, error “too many arguments” with exit code 1 (but NOT exit from the process!!!)

3 - If no path(2nd arg), it should be home dir
	- seach HOME path in the list of env variables, passed in the beginning of the program (shell.envp)
	- if no HOME in envp, error “HOME not set” with exit code 1 (e.g. in case if unset HOME);

4 - Change dir with function chdir(form unistd.h)
	- If chdir returns error, error “No such file or directory” with exit code 1 

5 - Update list of env (shell.envp);
 - if $OLDPWD was unset, add new env node to envp, else update value OLDPWD, value is PWD;
 - if $PWD was unset, add new env node to envp, else update value PWD, value is getcwd())
*/


/*
TESTS

*/
int	ft_builtin_cd(t_shell *shell, t_exec *exec_node)
{
	char *path;
	t_env *tmp_env;
	
	path = exec_node->av[1];
	tmp_env = malloc(sizeof(t_env));
	if (ft_arr_size (exec_node->av) > 2) //arr should be with null terminator
		return (ft_err_msg("cd", "too many arguments", NULL), ENO_GENERAL);
	else if (!path)
	{
		tmp_env = ft_get_env(*shell, "HOME");
		printf("test3\n");
		if (!tmp_env)
			return (ft_err_msg("cd", "HOME not set", NULL), ENO_GENERAL);
		else
		{
			path = tmp_env->value;
		}	
	}
	printf("path: %s\n", path);

	if (chdir(path) != ENO_SUCCESS)
		return (ft_err_msg("cd", path, "No such file or directory"), ENO_GENERAL);
	printf("test4\n");
	tmp_env = ft_get_env(*shell, "OLDPWD");
	if(tmp_env != NULL)
	{
		printf("OLDPWD: %s\n", tmp_env->value);	
		tmp_env = ft_get_env(*shell, "PWD");
		printf("PWD: %s\n", tmp_env->value);
		ft_update_env_value(shell->envp, "OLDPWD", tmp_env->value);
		// ft_print_env_lst(shell.envp);
		//free(tmp_env); //check don't need it
	}
	else
	{
		tmp_env = ft_get_env(*shell, "PWD");
		tmp_env = ft_dup_env_node(shell, "OLDPWD", tmp_env->value);
		printf("OLDPWD is unset, create a new node with OLDPWD, value is value of PWD\n");
		ft_lstadd_back(&shell->envp, ft_lstnew(tmp_env));
	}
	tmp_env = ft_get_env(*shell, "PWD"); // FIND BUG AS SEGFAULT!!
	if(tmp_env != NULL)
	{
	// 	free(tmp_env); //check malloc issues
		ft_update_env_value(shell->envp, "PWD", getcwd(NULL, 0));
	}
	else
	{
		printf("PWD is unset, create a new node with PWD, value is chdir()");
		tmp_env = ft_dup_env_node(shell, "PWD", getcwd(NULL, 0));
		ft_lstadd_back(&shell->envp, ft_lstnew(tmp_env));
	}
    return (ENO_SUCCESS);
}
