/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:52:28 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 18:33:10 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sgmnt_len(const char *str, int pos)
{
	int	counter;

	counter = 0;
	while (str[pos] && str[pos] != '\n')
	{
		pos++;
		counter++;
	}
	return (counter);
}

void	clean_list(t_token **list)
{
	t_token	*temp;
	t_token	*next;

	temp = *list;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->context);
		temp->context = NULL;
		free(temp);
		temp = next;
	}
	*list = NULL;
}

int	print_export(char *n_new)
{
	int		j;

	j = 0;
	printf("declare -x ");
	while (n_new[j++] != '=')
	{
		j--;
		printf("%c", n_new[j]);
		j++;
	}
	if (n_new[j] == '\0')
	{
		printf("\n");
		return (1);
	}
	printf("=\"");
	j--;
	while (n_new[j++] != '\0')
		printf("%c", n_new[j]);
	printf("\"\n");
	j = 0;
	return (0);
}

void	swap_node(t_env	*a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

t_env	*bubble_sort_lst(t_env *lst)
{
	int		flag;
	t_env	*tmp;
	t_env	*i;

	i = NULL;
	flag = 1;
	if (lst == NULL)
		return (NULL);
	while (flag == 1)
	{
		tmp = lst;
		flag = 0;
		while (tmp && tmp->next)
		{
			i = tmp->next;
			if (ft_strcmp(tmp->key, i->key) > 0)
			{
				swap_node(tmp, i);
				flag = 1;
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}
