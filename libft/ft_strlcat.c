/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:15:52 by mosokina          #+#    #+#             */
/*   Updated: 2024/04/29 10:16:22 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	i_s;
	size_t	srclen;
	size_t	i_d;

	i_s = 0;
	srclen = ft_strlen(src);
	destlen = ft_strlen(dst);
	i_d = destlen;
	if (destlen >= size)
		return (size + srclen);
	while ((src[i_s] != '\0') && (i_d < (size - 1)))
	{
		dst[i_d] = src[i_s];
		i_d ++;
		i_s ++;
	}
	dst[i_d] = '\0';
	return (srclen + destlen);
}
