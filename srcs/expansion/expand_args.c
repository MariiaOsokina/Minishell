/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:37:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/17 20:24:28 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static void ft_print_str_arr(char **arr)
// {
// 	if (!arr)
// 	{
// 		printf("(null array)\n");
// 		return;
// 	}

// 	for (int i = 0; arr[i] != NULL; i++)
// 	{
// 		printf("[%d] %s\n", i, arr[i]);
// 	}
// }

static void	ft_expand_variables(t_shell *shell, t_exec *exec_node)
{
	int		i;
	char	*expanded;

	i = 0;
	while (exec_node->av[i])
	{
		expanded = ft_var_expansion(shell, exec_node->av[i]);
		if (exec_node->av[i])
			free(exec_node->av[i]);
		exec_node->av[i] = expanded;
		// printf("expanded %s\n", exec_node->av[i]);
		i++;
	}
}

static void	ft_expand_word_splitting(t_exec *exec_node)
{
	int		i;
	char	**new_words;

	i = 0;
	while (exec_node->av[i])
	{
		new_words = ft_expand_word_split(exec_node->av[i]);
		// ft_print_str_arr(new_words);
		// ft_free_str_arr(new_words, ft_arr_size(new_words));
		if (new_words)
		{
			exec_node->av = ft_replace_args(exec_node->av, new_words, i);
			ft_free_str_arr(new_words, ft_arr_size(new_words));
		}
		i++;
	}
}

static void	ft_expand_globbing(t_exec *exec_node)
{
	int		i;
	// char	*quoted_removed;
	char	**filenames;

	i = 0;
	while (exec_node->av[i])
	{
		if (ft_scan_for_asterisk(exec_node->av[i]))
		{
			filenames = ft_get_filenames_arr(exec_node->av[i]);
			if (filenames)
			{
				exec_node->av = ft_replace_args(exec_node->av, filenames, i);
				ft_free_str_arr(filenames, ft_arr_size(filenames));
			}
		}
		i++;
	}
}

static void	ft_remove_quotes_in_args(t_exec *exec_node)
{
	int		i;
	char	*quoted_removed;

	i = 0;
	while (exec_node->av[i])
	{
		quoted_removed = ft_quote_removal(exec_node->av[i]);
		if (exec_node->av[i])
			free(exec_node->av[i]);
		exec_node->av[i] = quoted_removed;
		// printf("quoted_removed %s\n", exec_node->av[i]);
		i++;
	}
}

void	ft_expand_args(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node->av)
		return ;
	ft_expand_variables(shell, exec_node);
	// printf("after $\n");
	// ft_print_str_arr(exec_node->av); //for testing
	ft_delete_empty_arg(exec_node);
	// printf("after delete empty str arg\n");
	// ft_print_str_arr(exec_node->av); //for testing
	ft_clean_empty_strs(exec_node);
	ft_expand_word_splitting(exec_node);
	ft_expand_globbing(exec_node);
	// printf("after globbing\n");
	// ft_print_str_arr(exec_node->av); //for testing
	ft_remove_quotes_in_args(exec_node);
	// printf("after removing quotes\n");
	// ft_print_str_arr(exec_node->av); //for testing
	return ;
}
