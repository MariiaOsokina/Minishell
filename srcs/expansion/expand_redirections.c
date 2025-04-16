/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:57:02 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/16 19:05:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
Expand and validate a file name in redirection (like <, >, >>) by:

1 - Performing variable expansion (e.g., $VAR → value)

2 - Handling globbing/asterisk expansion (e.g., * → list of matching files)

3 - Checking for ambiguities in redirection

4 - Performing quote removal on the final string
*/
/*
int ft_expand_redir_name(t_shell *shell, t_in_out *io_node)
{
	char 	*expanded;
	// char 	**filenames;
	char	*quoted_removed;

	expanded = ft_var_expansion(shell, io_node->name);
	// printf("test expand redir: %s\n", expanded); //for testing
	if (!expanded || expanded[0] == '\0' || ft_count_words(expanded) > 1)
	{
		if (expanded)
			free(expanded);
		ft_err_msg (io_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
		return (ENO_GENERAL); // Malloc failure or similar
	}
	// // Asterisk (globbing) expansion
	// if (ft_scan_for_asterisk(expanded))
	// {
	// 	// Replace current argument with matched filenames
	// 	filenames = ft_get_filenames_arr(expanded);
	// 	if (!filenames || filenames[0] == NULL)
	// 	{
	// 		ft_free_str_arr(filenames, ft_arr_size(filenames));
	// 		if (expanded)
	// 			free(expanded);
	// 		expanded = NULL;
	// 	}
	// 	else if (ft_arr_size(filenames) > 1)
	// 	{
	// 		if (expanded)
	// 			free (expanded);
	// 		ft_print_str_arr(filenames); //for testing
	// 		ft_free_str_arr(filenames, ft_arr_size(filenames));
	// 		ft_err_msg (io_node->name, "ambiguous redirect", NULL); // for ex, < * $VAR = ""
	// 		return (ENO_GENERAL);
	// 	}
	// 	else if (ft_arr_size(filenames) == 1 && filenames[0])
	// 	{
	// 		if (expanded)
	// 			free(expanded);
	// 		expanded = ft_strdup(filenames[0]);
	// 		ft_free_str_arr(filenames, ft_arr_size(filenames));
	// 	}
	// }
	if (io_node->name)
		free(io_node->name);
	quoted_removed = ft_quote_removal(expanded);
	// printf("test after quote removed redir: %s\n", quoted_removed); for testing
	if (quoted_removed)
    	io_node->name = quoted_removed;
	else
			io_node->name = ft_strdup("");
	if (expanded)
		free(expanded);		
	return (ENO_SUCCESS);
}
*/


static int	ft_check_expanded(char *expanded, char *original)
{
	if (!expanded || expanded[0] == '\0' ||
        ft_count_words(expanded) > 1)
	{
		if (expanded)
			free(expanded);
		ft_err_msg(original, "ambiguous redirect", NULL);
		return (ENO_GENERAL);
	}
	return (ENO_SUCCESS);
}

static void ft_remove_quotes_in_redir(t_in_out *io_n, char *str)
{
	char	*quoted_removed;

	if (io_n->name)
		free(io_n->name);
	quoted_removed = ft_quote_removal(str);
	if (quoted_removed)
		io_n->name = quoted_removed;
	else
		io_n->name = ft_strdup("");
}

int	ft_expand_redir_name(t_shell *shell, t_in_out *io_node)
{
	char	*expanded;
	int		status;

	expanded = ft_var_expansion(shell, io_node->name);
	status = ft_check_expanded(expanded, io_node->name);
	if (status != ENO_SUCCESS)
		return (status);
	ft_remove_quotes_in_redir(io_node, expanded);
	if (expanded)
		free(expanded);
	return (ENO_SUCCESS);
}