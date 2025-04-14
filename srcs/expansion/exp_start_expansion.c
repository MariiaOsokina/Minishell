/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_start_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:37:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/15 00:19:42 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_rewrite_array(char **array, int size) {
    for (int i = 0; i < size; ++i) {
        char *new_str = ft_strdup(array[i]);
        if (!new_str) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        array[i] = new_str;
    }
}
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

void ft_expand_args(t_shell *shell, t_exec *exec_node)
{
	char 	*expanded;
	// char 	**filenames;
	int		i;
	int		size;
	char	*quoted_removed;

	
	size = ft_arr_size(exec_node->av);
	printf("size of array %d\n", size);
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
		printf("expanded %s\n", exec_node->av[i]);

		i++;
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
			char **filenames = ft_get_filenames_arr(exec_node->av[i]);
			if (filenames)
			{
				exec_node->av = ft_replace_args(exec_node->av, filenames, i);
				if (filenames)
					ft_arr_size(filenames);
				// `ft_replace_args` should handle memory cleanup and index update
				continue;
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

/*
Expand and validate a file name in redirection (like <, >, >>) by:

1 - Performing variable expansion (e.g., $VAR → value)

2 - Handling globbing/asterisk expansion (e.g., * → list of matching files)

3 - Checking for ambiguities in redirection

4 - Performing quote removal on the final string
*/
int ft_expand_redir_name(t_shell *shell, t_in_out *io_node)
{
	char 	*expanded;
	char 	**filenames;
	char	*quoted_removed;

	// Variable expansion
	expanded = ft_var_expansion(shell, io_node->name);
	if (!expanded || expanded[0] == '\0')
	{
		if (expanded)
			free(expanded);
		ft_err_msg (io_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL); // Malloc failure or similar
	}
	// Asterisk (globbing) expansion
	if (ft_scan_for_asterisk(expanded))
	{
		// Replace current argument with matched filenames
		filenames = ft_get_filenames_arr(expanded);
		if (!filenames || filenames[0] == NULL)
		{
			ft_free_str_arr(filenames, ft_arr_size(filenames));
			if (expanded)
				free(expanded);
			expanded = NULL;
		}
		else if (ft_arr_size(filenames) > 1)
		{
			if (expanded)
				free (expanded);
			ft_print_str_arr(filenames); //for testing
			ft_free_str_arr(filenames, ft_arr_size(filenames));
			ft_err_msg (io_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
			return (ENO_GENERAL);
		}
		else if (ft_arr_size(filenames) == 1 && filenames[0])
		{
			if (expanded)
				free(expanded);
			expanded = ft_strdup(filenames[0]);
			ft_free_str_arr(filenames, ft_arr_size(filenames));
		}
	}
	if (io_node->name)
		free(io_node->name);
	quoted_removed = ft_quote_removal(expanded);
	if (quoted_removed)
    	io_node->name = quoted_removed;
	else
			io_node->name = ft_strdup("");
	if (expanded)
		free(expanded);		
	return (ENO_SUCCESS);
}
