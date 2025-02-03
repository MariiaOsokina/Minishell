/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:49:55 by mosokina          #+#    #+#             */
/*   Updated: 2024/05/04 18:27:18 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 1)
		len ++;
	while (nbr != 0)
	{
		nbr /= 10;
		len ++;
	}
	return (len);
}

static long long	abs_val(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	unsigned int	nbr;

	len = nbr_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	sign = 0;
	if (n < 0)
		sign = 1;
	nbr = abs_val(n);
	*(str + len) = '\0';
	while (len--)
	{
		*(str + len) = '0' + (nbr % 10);
		nbr /= 10;
	}
	if (sign == 1)
		*str = '-';
	return (str);
}
