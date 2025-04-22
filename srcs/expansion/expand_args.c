/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:37:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/22 23:12:32 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void ft_print_str_arr(char **arr)
{
	if (!arr)
	{
		printf("(null array)\n");
		return;
	}

	for (int i = 0; arr[i] != NULL; i++)
	{
		printf("[%d] %s\n", i, arr[i]);
	}
}

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

/*NEW FUNCTION FOR TESTING*/
/*
ft_remove_arg_from_av
- reallocates the array, skips the unwanted index, and shifts the rest.
- frees the removed string and old array.
*/

char **ft_remove_arg_from_av(char **av, int index)
{
	int		i;
	int		j;
	// int		size;
	char	**new_av;

	if (!av)
		return (NULL);
	// size = 0;
	// while (av[size])
	// 	size++;
	// new_av = ft_calloc(size, sizeof(char *)); // size-1 for new, +1 for NULL
	new_av = ft_calloc(ft_arr_size(av), sizeof(char *));
	if (!new_av)
		return (NULL);
	i = 0;
	j = 0;
	while (av[i])
	{
		if (i != index)
			new_av[j++] = av[i];
		else
			free(av[i]); // free the one being removed
		i++;
	}
	free(av); // free the original array (not the strings, already moved/freed)
	return (new_av);
}

/*ft_expand_word_splitting
1- Checks for empty string before splitting.

2- Uses ft_expand_word_split() to split each word if needed.

3 - Removes the original argument and inserts split parts via ft_replace_args.

4 -
if (exec_node->av[i][0] == '\0')
correctly avoids removing quoted empty strings ("" is "\"\"", so it doesn't match '\0' at this point).*/

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
			continue; // don't increment i, we just shifted everything left
		}		
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

/*ft_expand_globbing():

Applies globbing only when * is detected outside quotes.

Replaces exec_node->av[i] with matching filenames.
*/

static void	ft_expand_globbing(t_exec *exec_node)
{
	int		i;
	char	**filenames;
	int		match_count;

	i = 0;
	while (exec_node->av[i])
	{
		if (ft_scan_for_asterisk(exec_node->av[i]))
		{
			match_count = ft_match_count(exec_node->av[i]);
			if (match_count > 0)
			{
				filenames = ft_get_filenames_arr(exec_node->av[i], match_count);
				if (filenames)
				{
					exec_node->av = ft_replace_args(exec_node->av, filenames, i);
					ft_free_str_arr(filenames, ft_arr_size(filenames));
				}
			}
			// else: do nothing, leave original pattern untouched
		}		
		i++;
	}
}

/*ft_remove_quotes_in_args
1 - Goes through each arg and removes quotes using ft_quote_removal.
2 - Properly frees the old strings and replaces them.
📌 Note: tp check that ft_quote_removal() correctly handles escaped quotes, nested quotes, and mixed quoting — that’s the one sensitive spot.
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
		// printf("quoted_removed %s\n", exec_node->av[i]);
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
	printf("after $\n");
	ft_print_str_arr(exec_node->av); //for testing
	// ft_delete_empty_arg(exec_node);
	// printf("after delete empty str arg\n");
	// ft_print_str_arr(exec_node->av); //for testing
	// ft_clean_empty_strs(exec_node);
	ft_expand_word_splitting(exec_node);
	printf("after word splitting and deleting empty expanded string empty\n");
	ft_print_str_arr(exec_node->av); //for testing	ft_expand_globbing(exec_node);
	ft_expand_globbing(exec_node);
	printf("after globbing\n");
	ft_print_str_arr(exec_node->av); //for testing
	ft_remove_quotes_in_args(exec_node);
	printf("after removing quotes\n");
	ft_print_str_arr(exec_node->av); //for testing
	return ;
}
