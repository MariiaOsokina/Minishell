/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:37:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/26 01:16:28 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_print_str_arr(char **arr) // JUST FOR TESTING
// {
// 	if (!arr)
// 	{
// 		printf("(null array)\n");
// 		return ;
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
		i++;
	}
}

/*ft_expand_word_splitting
1- Checks for empty string before splitting.

2- Uses ft_expand_word_split() to split each word if needed.

3 - Removes the original argument and inserts split parts 
via ft_replace_args.

4 -
if (exec_node->av[i][0] == '\0')
correctly avoids removing quoted empty strings 
("" is "\"\"", so it doesn't match '\0' at this point).*/

static void	ft_expand_word_splitting(t_exec *exec_node)
{
	int		i;
	char	**new_words;

	i = 0;
	while (exec_node->av[i])
	{
		if (exec_node->av[i][0] == '\0')
		{
			exec_node->av = ft_remove_arg_from_av(exec_node->av, i);
			continue ;
		}
		new_words = ft_expand_word_split(exec_node->av[i]);
		if (new_words)
		{
			exec_node->av = ft_replace_args(exec_node->av, new_words, i);
			ft_free_str_arr(new_words, ft_arr_size(new_words));
		}
		i++;
	}
}

/*ft_expand_globbing():

Applies globbing only when * is detected outside quotes.

Replaces exec_node->av[i] with matching filenames.
*/

// static void	ft_expand_globbing(t_exec *exec_node)
// {
// 	int		i;
// 	char	**filenames;
// 	int		match_count;
// 	char	*tmp_quoted_removed;

// 	i = 0;
// 	while (exec_node->av[i])
// 	{
// 		if (ft_scan_for_asterisk(exec_node->av[i]))
// 		{
// 			tmp_quoted_removed = ft_quote_removal(exec_node->av[i]);
// 			match_count = ft_match_count(tmp_quoted_removed);
// 			// printf("match_count %d\n", match_count);
// 			if (match_count > 0)
// 			{
// 				filenames = ft_get_filenames_arr(tmp_quoted_removed, match_count);
// 				if (filenames)
// 				{
// 					exec_node->av = ft_replace_args(exec_node->av, filenames, i);
// 					ft_free_str_arr(filenames, ft_arr_size(filenames));
// 				}
// 			}
// 			if (tmp_quoted_removed)
// 				free(tmp_quoted_removed);
// 		}
// 		i++;
// 	}
// }

static void	ft_expand_globbing(t_exec *exec_node)
{
	int	i;

	i = 0;
	while (exec_node->av[i])
	{
		if (ft_scan_for_asterisk(exec_node->av[i]))
			ft_globbing_in_arg(exec_node, i);
		i++;
	}
}

/*ft_remove_quotes_in_args
1 - Goes through each arg and removes quotes using ft_quote_removal.
2 - Properly frees the old strings and replaces them.
📌 Note: tp check that ft_quote_removal() correctly handles 
escaped quotes, nested quotes, and mixed quoting — that’s the one sensitive spot.
*/

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
		i++;
	}
}

/* ft_expand_args – Main Entry Point

1 - Variable Expansion → $VAR, $HOME, $? etc.

2 - Word Splitting → "a b" stays one word, but a b splits into two.

3 - Globbing → *, file?.txt etc.

4- Quote Removal → "arg" → arg, but only after all expansions are done.*/

void	ft_expand_args(t_shell *shell, t_exec *exec_node)
{
	if (exec_node->av == NULL || exec_node->av[0] == NULL)
		return ;
	ft_expand_variables(shell, exec_node);
	ft_expand_word_splitting(exec_node);
	// printf("after word splitting and deleting empty expanded string empty\n");
	// ft_print_str_arr(exec_node->av); //for testing
	ft_expand_globbing(exec_node);
	// printf("after globbing\n");
	// ft_print_str_arr(exec_node->av); //for testing
	ft_remove_quotes_in_args(exec_node);
	// printf("after remove quptes\n");
	// ft_print_str_arr(exec_node->av); //for testing
	return ;
}
