/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:28:20 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/08 14:56:19 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*STEPS:
1 - NOTE: Options are not in the Minishell Subject!
2 - If just cmd without argos, just return with exit code 0;
3 - Loop argos. 
4 - If arg is key in envp, unset this key=value, 
i.e. delete the node from list. 
*/

/*
static char	*ft_unset_key(t_shell *shell, const char *key)
{
	t_list	*current_list;
	t_list	*tmp_prev_list;
	t_env	*env_content;
	t_list	*to_free;

	// to_free = NULL;
	tmp_prev_list = NULL;
	current_list = shell->envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (ft_strcmp(env_content->key, key) == 0)
		{
			// Update the list pointers
			if (tmp_prev_list)
				tmp_prev_list->next = current_list->next;
			else
				shell->envp = current_list->next;
			ft_free_env_node(env_content);
			// Free the node itself
			to_free = current_list;
			current_list = current_list->next;
			free (to_free);
			continue ;
		}
		tmp_prev_list = current_list;
		current_list = current_list->next;
	}
	return (NULL);
}
*/

// static 	void ft_unset_key(t_shell *sh, t_list **cur, t_list **prev, t_env *env_c)
// {
// 	t_list	*to_free;

// 	to_free = NULL;

// 	// Update the list pointers
// 	if (*prev)
// 		*(prev)->next = *cur->next;
// 	else
// 		sh->envp = *(cur)->next;
// 	ft_free_env_node(env_c);
// 	// Free the node itself
// 	to_free = *cur;
// 	*cur = *(cur)->next;
// 	free (to_free);
// }

// static void	ft_check_key(t_shell *shell, const char *key)
// {
// 	t_list	*current_list;
// 	t_list	*tmp_prev_list;
// 	t_env	*env_content;

// 	tmp_prev_list = NULL;
// 	current_list = shell->envp;
// 	while (current_list)
// 	{
// 		env_content = (t_env *)current_list->content;
// 		if (ft_strcmp(env_content->key, key) == 0)
// 		{
// 			ft_unset_key(shell, current_list, tmp_prev_list, env_content);
// 			continue ;
// 		}
// 		tmp_prev_list = current_list;
// 		current_list = current_list->next;
// 	}
// 	return ;
// }

static void	ft_unset_key(t_shell *sh, t_list *cur, t_list *prev)
{
	t_env	*env_c;

	env_c = (t_env *)cur->content;
	if (prev)
		prev->next = cur->next;
	else
		sh->envp = cur->next;
	ft_free_env_node(env_c);
	free(cur);
}

void	ft_check_key(t_shell *shell, const char *key)
{
	t_list	*cur;
	t_list	*prev;
	t_env	*env_c;
	t_list	*to_delete;

	cur = shell->envp;
	prev = NULL;
	while (cur)
	{
		env_c = (t_env *)cur->content;
		if (ft_strcmp(env_c->key, key) == 0)
		{
			to_delete = cur;
			cur = cur->next;
			ft_unset_key(shell, to_delete, prev);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

int	ft_builtin_unset(t_shell *shell, t_exec *exec_node)
{
	char	**unset_args;
	int		i;

	unset_args = &(exec_node->av[1]);
	i = 0;
	if (!unset_args[0])
		return (ENO_SUCCESS);
	while (unset_args[i])
	{
		ft_check_key(shell, unset_args[i]);
		i ++;
	}
	return (ENO_SUCCESS);
}
