/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:17:43 by mosokina          #+#    #+#             */
/*   Updated: 2024/05/08 13:17:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_puthexa(int n, char format)
{
	int				len;
	char			*base;
	unsigned int	nbr;

	nbr = (unsigned int)n;
	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr > (ft_strlen(base) - 1))
		len += ft_puthexa((nbr / ft_strlen(base)), format);
	len += ft_putchar(*(base + (nbr % ft_strlen(base))));
	return (len);
}
