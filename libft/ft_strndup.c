#include "libft.h"

char	*ft_strndup(const char *str, size_t size)
{
	size_t	i;
	char	*dest;

	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str, size + 1);
	return (dest);
}

/*This is a manual implementation*/
// char	*ft_strndup(const char *str, size_t size)
// {
// 	size_t i;
// 	char *dest;

// 	i = 0;
// 	dest = malloc(sizeof(char) * (size + 1));
// 	if (!dest)
// 		return (NULL);
// 	while (str[i] && (i < size))
// 	{
// 		dest[i] = str[i];
// 		i++;
// 	}
// 	dest[i] = 0;
// 	return (dest);
// }
