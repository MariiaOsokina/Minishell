/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:09:10 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/18 10:09:51 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && ft_strchr(set, s[start]))
		start++;
	end = ft_strlen((char *)s);
	if (start == end)
		return (ft_strdup(""));
	while (end > start && ft_strchr(set, s[end - 1]))
		end--;
	trimmed = ft_substr(s, start, end - start);
	return (trimmed);
}
