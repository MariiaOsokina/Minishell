/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:56:36 by mosokina          #+#    #+#             */
/*   Updated: 2024/04/27 22:03:10 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while ((big[i + j] == little[j]) && (big[i + j]) && (i + j < len))
		{
			j ++;
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		i ++;
		j = 0;
	}
	return (0);
}
