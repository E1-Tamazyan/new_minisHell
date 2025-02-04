/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:48:10 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 18:07:35 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_skip(int i, int *indexes, int index_count)
{
	int	k;

	k = 0;
	while (k < index_count)
	{
		if (indexes[k] == i)
			return (1);
		k++;
	}
	return (0);
}

static char	*rm_quoted_pos(char *str, int *indexes, int index_count, int len)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(len - index_count + 1);
	if (!res)
		return (NULL);
	while (i < len)
	{
		if (!find_skip(i, indexes, index_count))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free_set_null(str);
	return (res);
}

static char	*remove_outer_quotes(t_shell *general, char *str, int i, int i_c)
{
	int	len;
	int	*indexes;

	len = ft_strlen(str);
	indexes = ft_calloc(len, sizeof(int));
	check_malloc(general, indexes);
	while (str[i])
	{
		if (!general->sg_quote && str[i] == '\"')
		{
			general->db_quote = !general->db_quote;
			indexes[i_c++] = i;
		}
		else if (!general->db_quote && str[i] == '\'')
		{
			general->sg_quote = !general->sg_quote;
			indexes[i_c++] = i;
		}
		i++;
	}
	str = rm_quoted_pos(str, indexes, i_c, len);
	if (!str)
		return (free(indexes), NULL);
	return (free(indexes), str);
}

t_token	*remove_extra_quotes(t_shell *general)
{
	t_token	*head;

	head = general->tok_lst;
	general->db_quote = 0;
	general->sg_quote = 0;
	while (general->tok_lst != NULL)
	{
		general->tok_lst->context = remove_outer_quotes(general,
				general->tok_lst->context, 0, 0);
		general->tok_lst = general->tok_lst->next;
	}
	general->tok_lst = head;
	return (general->tok_lst);
}
