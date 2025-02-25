/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:36:39 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/25 14:02:50 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*ml_ptr;

	ml_ptr = (char *)malloc(ft_strlen(s) + 1);
	if (ml_ptr == NULL)
		return (NULL);
	return (ft_strcpy(ml_ptr, s));
}
