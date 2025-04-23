/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:07:31 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/23 11:04:18 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i ++;
	return (i);
}

void	ft_free_str_arr(char **arr, int count)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_count_str_arr(char **arr)
{
	int	count;

	count = 0;
	while (arr && arr[count])
		count++;
	return (count);
}
