#include "minishell.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str1;

	str1 = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		str1[i] = c;
		i++;
	}
	return (str1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if ((count != 0 && size > 65536) || (size != 0 && count > 65536))
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	str = ft_memset(str, '\0', count * size);
	return (str);
}