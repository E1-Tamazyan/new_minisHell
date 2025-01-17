/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_allocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:59:51 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/17 11:03:16 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_lst(t_cmd_lst *cmd_lst)
{
	t_cmd_lst *temp;
	int i;

	i = 0;
	temp = NULL;
	while (cmd_lst)
	{
		temp = cmd_lst;
		free(temp->cmd);
		if (temp->args)
		{
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		free(temp);
		cmd_lst = cmd_lst->next;
	}
}
void	free_ptr(void *ptr)
{
	
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	free_node(t_env *node)
{
	if (node->key)
	{
		free(node->key);
		node->key = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}
