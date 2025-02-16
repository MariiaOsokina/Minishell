/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:00:51 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/05 10:00:54 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "../../includes/minishell_flo.h"

/*
* Update working directory and old working directory in env-variables
* and the data struct.
*/
void	update_wds(t_data *data, char *cwd)
{
	char	*tmp;

	if (get_env_var_i(data->env, "OLDPWD=") >= 0)
	{
		if (get_env_var_i(data->env, "PWD=") >= 0)
			tmp = ft_strjoin("OLDPWD",
					strchr(data->env[get_env_var_i(data->env, "PWD=")], '='));
		else
			tmp = ft_strjoin("OLDPWD=", "");
		if (!tmp)
			return ;
		set_env_var(data, tmp);
		free(tmp);
	}
	if (get_env_var_i(data->env, "PWD=") >= 0)
	{
		tmp = ft_strjoin("PWD=", cwd);
		if (!tmp)
			return ;
		set_env_var(data, tmp);
		free(tmp);
	}
	free(data->old_working_dir);
	data->old_working_dir = data->working_dir;
	data->working_dir = ft_strdup(cwd);
}

/*
* Changes the current working directory and updates the 
* env-var OLDPWD and PWD
*	Return EXIT_SUCCESS on success and EXIT_FAILURE on failure
*/
int	change_dir(t_data *data, char *path)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	int		ret;

	ret = chdir(path);
	if (ret != 0)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		return (err_msg("cd", path, strerror(errno)), EXIT_FAILURE);
	}
	tmp = getcwd(cwd, PATH_MAX);
	(void)tmp;
	update_wds(data, cwd);
	return (EXIT_SUCCESS);
}

/*
* check if args refers to changing to home directory
*	yes -> return path to home
*	no  -> return NULL
*/
int	check_dir_to_home(char **args)
{
	if (!args || !args[0])
		return (-1);
	else if (get_size_ptr(args) >= 2 && ft_strncmp(args[0], "--", 3) == 0)
		return (1);
	else if (args[0][0] == '\0' || ft_strncmp(args[0], "--", 3) == 0)
		return (-1);
	return (0);
}

/*
* Imitates the builtin function "cd" of bash
*	change the working directory and store the old working
*	error (cd: <Input>: No such file or directory) if dir doesn't exist
*		and "cd: too many arguments" if more than one arguments
*	absolute path:
*			- must start with '/'
*			- can but doesn't have to end with '/'
*	relative path:
*			- can but don't have to start with '\' or '/'
*			- can but doesn't have to end with '/'
*			- interpret '..' as one directory up
*			- don't do anything if only "." is inserted
*	arg == 
*			'--' -> change working directory to <HOME> (from env)
*			'-'  -> change to previous directory
*	no arguments: change working directory to <HOME> (from env)
*/
int	builtin_cd(t_data *data, char **args)
{
	int		i_arg;
	int		i;

	i_arg = check_dir_to_home(args);
	if ((i_arg == 1 && get_size_ptr(args) > 2)
		|| (i_arg == 0 && get_size_ptr(args) > 1))
		return (err_msg("cd", "too many arguments", NULL), EXIT_FAILURE);
	else if (i_arg < 0)
	{
		i = get_env_var_i(data->env, "HOME=");
		if (i < 0)
			return (err_msg("cd", "HOME not set", NULL), EXIT_FAILURE);
		return (change_dir(data, ft_strchr(data->env[i], '=') + 1));
	}
	if (!strncmp(args[0], "-", 2))
	{
		i = get_env_var_i(data->env, "OLDPWD=");
		if (i < 0)
			return (err_msg("cd", "OLDPWD not set", NULL), EXIT_FAILURE);
		else
			return (change_dir(data, ft_strchr(data->env[i], '=') + 1));
	}
	return (change_dir(data, args[i_arg]));
}