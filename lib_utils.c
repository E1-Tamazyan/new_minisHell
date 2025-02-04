/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:45:48 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/02 14:04:31 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*my_lstnew(char *key, char *value) // contains blabla = blabla=bla
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node -> next = NULL;
	return (node);
}

void	ft_lstadd_back(t_env *lst, t_env *node)
{
	t_env	*current;

	if (!node)
		return ;
	if (!lst)
	{
		lst = node;
		return ;
	}
	current = lst;
	while (current -> next)
		current = current -> next;
	current->next = node;
}

void	ft_strlcpy_2(char *dest, const char *src, int size, int pos)
{
	int	i;

	i = 0;
	while (i < size && src[pos] && src[pos] != '\n')
	{
		dest[i] = src[pos];
		i++;
		pos++;
	}
	dest[i] = '\0';
}

void	ft_strlcpy(char *dest, const char *src, int size, int pos)
{
	int	i;

	i = 0;
	while (i < size && src[pos] && src[pos] != '=')
	{
		dest[i] = src[pos];
		i++;
		pos++;
	}
	dest[i] = '\0';
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		res;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			res = (int)(unsigned char)s1[i] - (int)(unsigned char)s2[i];
			return (res);
		}
		i++;
	}
	return (0);
}
