/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:21:46 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 17:21:48 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t size)
{
	char	*dest;

	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str, size + 1);
	return (dest);
}
