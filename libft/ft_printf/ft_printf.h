/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:10:31 by mosokina          #+#    #+#             */
/*   Updated: 2024/05/13 16:10:40 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

int				ft_printf(const char *str, ...);
int				ft_putaddress(void *ptr);
int				ft_putchar(char c);
int				ft_puthexa(int n, char format);
int				ft_putnbr(int n);
int				ft_putstr(char const *s);
int				ft_putunsigned(unsigned int n);
// unsigned int	ft_strlen(const char *s);

#endif
