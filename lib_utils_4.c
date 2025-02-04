/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:37:23 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/02 18:32:19 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_list(t_token *prev, t_token *current)
{
	if (prev)
		prev->next = current->next;
	if (current->context)
		free(current->context);
	free(current);
}

t_token	*ft_lst_delone(t_token **lst, t_token *node)
{
	t_token	*current;
	t_token	*prev;

	if (!lst || !*lst || !node)
		return (NULL);
	if (*lst == node)
	{
		current = (*lst)->next;
		free((*lst)->context);
		free(*lst);
		*lst = current;
		return (current);
	}
	prev = NULL;
	current = *lst;
	while (current && current != node)
	{
		prev = current;
		current = current->next;
	}
	if (current == node)
		ft_remove_list(prev, current);
	return (prev->next);
}

void	list_add_back_cmd(t_cmd_lst **lst, t_cmd_lst *n_new)
{
	t_cmd_lst	*add;

	add = *lst;
	if (!n_new)
		return ;
	if (!*lst)
		*lst = n_new;
	else
	{
		while (add->next != NULL)
			add = add->next;
		add->next = n_new;
		n_new->next = NULL;
	}
}

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

void	cmd_stuff(t_shell *general)
{
	general->tok_lst = remove_extra_quotes(general);
	check_heredoc_limit(general);
	create_cmd_lst(general);
	clean_list(&general->tok_lst);
}
