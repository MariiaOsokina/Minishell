/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:29:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/10 22:00:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

//in progress, needs to be tested


t_env	*ft_get_env(t_list *envp, char *check_key)
{
	t_list	*current_list;
	t_env	*env_content;

	current_list = envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, check_key))
			return (env_content);
        current_list = current_list->next;
	}
	return (NULL);
}


//for export and cd
void	ft_update_env_value(t_list *envp, char *key, char *new_value)
{
	t_list	*current;
	t_env	*env_content;

	current = envp;
	while (current)
	{
		env_content = (t_env *)current->content;
		if (!ft_strcmp(env_content->key, key))
		{
            printf("need to be updated %s\n", env_content->value);
			// if (new_value)
            //     free(env_content->value);
			env_content->value = ft_strdup(new_value); //check malloc issues;
			printf("has been updated %s\n", env_content->value);
			return ;
		}
		current = current->next;
	}
	return ;
}

// //for export and ?cd
// int	ft_add_envlist(t_list *envp, char *key, char *value)
// {
// 	ft_lstadd_back(&envp, ft_lstnew(new_env_content(key, value))); // is back right//or alphabetic order??
// 	return (ENO_SUCCESS);
// }

// static t_env	*ft_extract_key_value(char *export_arg, t_env *new_env) //check no malloc!!
// {
// 	int	i;

// 	i = 0;
// 	while (export_arg[i])
// 	{
// 		if (export_arg[i] == '=')
// 			return (ft_substr(export_arg, 0, i)); //no malloc
// 		i++;
// 	}
// 	return (new_env);
// }

// static char	*ft_extract_value(char *export_arg) //check no malloc!!
// {
// 	int	i;

// 	i = 0;
// 	while (export_arg[i])
// 	{
// 		if (export_arg[i] == '=')
// 			if (export_arg[i + 1])
// 			return (&(export_arg[i + 1])); //no malloc //check quotes(is it parsing part)
// 		i++;
// 	}
// 	return (NULL); //check is it NULL or empty str with "\0"??
// }

int ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i ++;
	return (i);
}