/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:20:51 by mosokina          #+#    #+#             */
/*   Updated: 2024/05/08 13:20:53 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	rec_print(unsigned long nbr)
{
	int				len;
	char			*base;

	len = 0;
	base = "0123456789abcdef";
	if (nbr > (ft_strlen(base) - 1))
		len += rec_print(nbr / ft_strlen(base));
	len += ft_putchar(*(base + (nbr % ft_strlen(base))));
	return (len);
}

int	ft_putaddress(void *ptr)
{
	unsigned long	nbr;
	int				len;

	nbr = (unsigned long)ptr;
	len = ft_putstr("0x");
	len += rec_print(nbr);
	return (len);
}
