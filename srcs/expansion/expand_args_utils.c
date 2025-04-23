/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:36:46 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/23 11:42:43 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char **av = {"", "apple", "", "banana", NULL};
Result after ft_remove_empty_strings(av):

Memory for empty strings is freed.

av itself is freed.

You get back: {"apple", "banana", NULL}.*/

// static int	count_non_empty(char **av)
// {
// 	int	count;

// 	count = 0;
// 	while (av && *av)
// 	{
// 		if (**av != '\0')
// 			count++;
// 		av++;
// 	}
// 	return (count);
// }

// static char	**ft_remove_empty_strings(char **av)
// {
// 	int		count;
// 	char	**new_av;
// 	int		j;
// 	int		i;

// 	i = 0;
// 	j = 0;
// 	count = count_non_empty(av);
// 	new_av = malloc((count + 1) * sizeof(char *));
// 	if (!new_av)
// 		return (NULL);
// 	while (av[i])
// 	{
// 		if (av[i][0] != '\0')
// 			new_av[j++] = av[i];
// 		else
// 			free(av[i]);
// 		i++;
// 	}
// 	new_av[j] = NULL;
// 	free(av);
// 	return (new_av);
// }

// void	ft_delete_empty_arg(t_exec *exec_node)
// {
// 	int		i;

// 	i = 0;
// 	while (exec_node->av[i])
// 	{
// 		if (!strcmp(exec_node->av[i], ""))
// 		{
// 			exec_node->av = ft_remove_empty_strings(exec_node->av);
// 			break ;
// 		}
// 		i++;
// 	}
// }

/*arg = strdup("hello''world\"\"!");
After ft_clean_empty_strs_in_arg(arg):

Removes '' and ""

Returns: "helloworld!"*/

// static char	*ft_clean_empty_strs_in_arg(char *arg)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*tmp;
// 	char	*ret;
// 	size_t	dstsize;

// 	if ((arg[0] == '\'' && arg[1] == '\'' && !arg[2])
// 		|| (arg[0] == '"' && arg[1] == '"' && !arg[2]))
// 		return (ft_strdup(arg));// malloc?
// 	tmp = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
// 	i = 0;
// 	j = 0;
// 	while (arg[i])
// 	{
// 		if ((arg[i] == '\'' && arg[i + 1] == '\'')
// 			|| (arg[i] == '"' && arg[i + 1] == '"'))
// 			i += 2;
// 		else
// 			tmp[j++] = arg[i++];
// 	}
// 	free(arg);
// 	dstsize = ft_strlen(tmp) + 1;
// 	ret = ft_calloc(dstsize, sizeof(char));
// 	return (ft_strlcpy(ret, tmp, dstsize), free(tmp), ret);
// }

// void	ft_clean_empty_strs(t_exec *exec_node)
// {
// 	int		i;

// 	i = 0;
// 	while (exec_node->av[i])
// 	{
// 		exec_node->av[i] = ft_clean_empty_strs_in_arg(exec_node->av[i]);
// 		i++;
// 	}
// }
