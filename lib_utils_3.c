/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:04:59 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/17 11:06:42 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 5
// ******************
// ****** FULL ******
// ******************

void	ft_strcpy_3(char *s1, const char *s2, int start_s1, int start_s2)
{
	while (s2[start_s2])
	{
		s1[start_s1] = s2[start_s2];
		start_s1++;
		start_s2++;
	}
	s1[start_s1] = s2[start_s2];
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

int	ft_isalnum(int arg)
{
	if ((arg >= 48 && arg <= 57) || (arg >= 65 && arg <= 90)
		|| (arg > 96 && arg < 123))
		return (1);
	else
		return (0);
}
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