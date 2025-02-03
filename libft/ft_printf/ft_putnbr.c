/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:18:26 by mosokina          #+#    #+#             */
/*   Updated: 2024/05/08 13:18:28 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int				len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			len += write (1, "-2", 2);
			n = 147483648;
		}
		else
		{
			len += ft_putchar('-');
			n = n * -1;
		}
	}
	if (n >= 10)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr((n % 10));
	}
	else
		len += ft_putchar('0' + n);
	return (len);
}
