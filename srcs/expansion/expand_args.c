/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:37:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/17 01:52:19 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




/* ft_expand_args function processes command arguments in multiple steps typical of a shell:
-  variable expansion, 
- word splitting, 
- globbing (wildcard expansion), 
-  quote removal. */

/*
void ft_expand_args(t_shell *shell, t_exec *exec_node)
{
	char 	*expanded;
	char 	**filenames;
	char	**new_words;
	int		i;
	int		size;
	char	*quoted_removed;

	//check the new AST parsing and delete if not needed
	size = ft_arr_size(exec_node->av);
	// printf("size of array %d\n", size);
	ft_rewrite_array(exec_node->av, size);
	ft_print_str_arr(exec_node->av);

	i = 0;
	// Variable expansion
	while (exec_node->av[i])
	{
		expanded = ft_var_expansion(shell, exec_node->av[i]);
		if (exec_node->av[i])
			free(exec_node->av[i]);
		exec_node->av[i] = expanded;
		printf("expanded %s\n", exec_node->av[i]); //for testing
		i++;
	}
	i = 0;
	// Word splitting
	while (exec_node->av[i])
	{
		new_words = ft_expand_word_split(exec_node->av[i]);
		if (new_words)
		{
			exec_node->av = ft_replace_args(exec_node->av, new_words, i);
			ft_free_str_arr(new_words, ft_arr_size(new_words));
		}
		i ++;
	}
	i = 0;
	// Asterisk (globbing) expansion
	while (exec_node->av[i])
	{
		if (ft_scan_for_asterisk(exec_node->av[i]))
		{
			quoted_removed = ft_quote_removal(exec_node->av[i]);
			if (exec_node->av[i])
				free(exec_node->av[i]);
			exec_node->av[i] = quoted_removed;
			printf("quoted_removed %s\n", exec_node->av[i]);
			//check Asterisk is not inside the quotes
			// Replace current argument with matched filenames
			filenames = ft_get_filenames_arr(exec_node->av[i]);
			if (filenames)
			{
				exec_node->av = ft_replace_args(exec_node->av, filenames, i);
				if (filenames)
					ft_free_str_arr(filenames, ft_arr_size(filenames));
			}
		}
		i++;
	}
	i = 0;
	// Quote removal
	while (exec_node->av[i])
	{
		quoted_removed = ft_quote_removal(exec_node->av[i]);
		if (exec_node->av[i])
			free(exec_node->av[i]);
		exec_node->av[i] = quoted_removed;
		printf("quoted_removed %s\n", exec_node->av[i]);
		i++;
	}
}
*/

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

// static void	ft_expand_word_splitting(t_exec *exec_node)
// {
// 	int		i;
// 	char	**new_words;

// 	i = 0;
// 	while (exec_node->av[i])
// 	{
// 		new_words = ft_expand_word_split(exec_node->av[i]);
// 		if (new_words)
// 		{
// 			exec_node->av = ft_replace_args(exec_node->av, new_words, i);
// 			ft_free_str_arr(new_words, ft_arr_size(new_words));
// 		}
// 		i++;
// 	}
// }

// static void	ft_expand_globbing(t_exec *exec_node)
// {
// 	int		i;
// 	char	*quoted_removed;
// 	char	**filenames;

// 	i = 0;
// 	while (exec_node->av[i])
// 	{
// 		if (ft_scan_for_asterisk(exec_node->av[i]))
// 		{
// 			quoted_removed = ft_quote_removal(exec_node->av[i]);
// 			if (exec_node->av[i])
// 				free(exec_node->av[i]);
// 			exec_node->av[i] = quoted_removed;
// 			printf("quoted_removed %s\n", exec_node->av[i]);
// 			filenames = ft_get_filenames_arr(exec_node->av[i]);
// 			if (filenames)
// 			{
// 				exec_node->av = ft_replace_args(exec_node->av, filenames, i);
// 				ft_free_str_arr(filenames, ft_arr_size(filenames));
// 			}
// 		}
// 		i++;
// 	}
// }

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
	// ft_expand_word_splitting(exec_node);
	// ft_expand_globbing(exec_node);
	ft_remove_quotes_in_args(exec_node);
	return ;
}
