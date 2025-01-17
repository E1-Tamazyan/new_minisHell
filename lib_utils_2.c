/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:14:51 by etamazya          #+#    #+#             */
/*   Updated: 2025/01/17 11:06:33 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 4
// ******************
// ****** FULL ******
// ******************

size_t	my_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen((char *)src);
	if (dstsize && dst)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

char	*str_join(char const *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	check_malloc(ptr);
	my_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	my_strlcpy(ptr + ft_strlen(s1), s2, (ft_strlen(s2) + 1));
	ptr[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ptr);
}

void	ft_strcpy(char *s1, const char *s2, int start, int len)
{
	int	i;
 
	i = 0;
	while (s2[start] && i < len)
	{
		s1[i] = s2[start];
		i++;
		start++;
	}
}
void	ft_strcpy_2(char *s1, const char *s2, int start, int len)
{
	int	i;
 
	i = 0;
	while (s2[i] && i < len)
	{
		s1[start] = s2[i];
		i++;
		start++;
	}
}
