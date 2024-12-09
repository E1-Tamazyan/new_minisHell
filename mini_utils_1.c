/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:50:05 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/09 20:00:27 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_print_dollar(const char *context, t_env *env_lst, int i)
{
	int		end;
	char	*var;
	t_env	*tmp;

	end = i;
	tmp = env_lst;
	if (!context)
		return (-1);
	while (context[end] && (context[end] != ' '
			&& (context[end] < 9 || context[end] > 13 || context[end] != '$')))
		end++;
	var = ft_substr(context, (unsigned int)i, (end - i));
	if (!var)
		return (1);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
			return (printf("%s\n", tmp->value), 0);
		tmp = tmp->next;
	}
	free(var);
	return (1);
}

short	del_t_node(t_token *lst)
{
	t_token	*tmp;

	if (lst == NULL || lst->next == NULL)
		return (-1);
	tmp = lst->next;
	lst->next = tmp->next;
	// lst->next = lst->next->next;
	free(tmp->context);
	free(tmp);
	return (0);
}

void	clean_env_list(t_env **list)
{
	t_env	*temp;
	t_env	*next;

	temp = *list;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*list = NULL;
}
