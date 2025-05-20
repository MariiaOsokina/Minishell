/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixed_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:44:52 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/29 18:45:14 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	populate_args(t_list **curr, char **args, int i)
{
	int	count;

	count = 0;
	if (i > 0)
		count = i;
	while ((*curr) && ((t_token *)(*curr)->content)->type == WORD)
	{
		args[count] = ft_strdup(((t_token *)(*curr)->content)->value);
		count++;
		next_token(curr);
	}
	args[count] = NULL;
}

void	copy_and_populate(char **av, t_list **curr, char **args)
{
	int	i;

	i = 0;
	while (av[i])
	{
		args[i] = ft_strdup(av[i]);
		i++;
	}
	args[i] = NULL;
	populate_args(curr, args, i);
	i = -1;
	while (av[++i])
		free(av[i]);
	free(av);
}
