/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:16:54 by mosokina          #+#    #+#             */
/*   Updated: 2024/05/08 13:16:56 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// unsigned int	ft_strlen(const char *s)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i ++;
// 	}
// 	return (i);
// }

int	ft_putstr(char const *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}
