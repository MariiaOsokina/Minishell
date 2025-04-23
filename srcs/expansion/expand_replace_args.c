/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:47:07 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/23 10:51:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_copy_before_index(char **dst, char **src, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		dst[i] = src[i];
		i++;
	}
}

static char	**ft_duplicate_items(char **items, int count)
{
	int		i;
	char	**copy;

	i = 0;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	while (i < count)
	{
		copy[i] = ft_strdup(items[i]);
		if (!copy[i])
		{
			while (i > 0)
			{
				i--;
				free(copy[i]);
			}
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	ft_insert_new_items(char **dst, char **items, int start, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dst[start + i] = items[i];
		i++;
	}
}

static void	ft_copy_after_index(char **dst, char **src, int ind, int new_l)
{
	int	old_len;
	int	i;
	int	j;

	i = ind + 1;
	j = ind + new_l;
	old_len = ft_count_str_arr(src);
	while (i < old_len)
		dst[j++] = src[i++];
}

char	**ft_replace_args(char **old_args, char **new_items, int index)
{
	int		old_len;
	int		new_len;
	int		new_total;
	char	**new_args;
	char	**temp_items;

	old_len = ft_count_str_arr(old_args);
	new_len = ft_count_str_arr(new_items);
	new_total = old_len - 1 + new_len;
	new_args = malloc(sizeof(char *) * (new_total + 1));
	if (!new_args)
		return (NULL);
	temp_items = ft_duplicate_items(new_items, new_len);
	if (!temp_items)
		return (free(new_args), NULL);
	ft_copy_before_index(new_args, old_args, index);
	if (old_args[index])
		free(old_args[index]);
	ft_insert_new_items(new_args, temp_items, index, new_len);
	ft_copy_after_index(new_args, old_args, index, new_len);
	new_args[new_total] = NULL;
	free(temp_items);
	free(old_args);
	return (new_args);
}
