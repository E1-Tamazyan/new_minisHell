/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:32:50 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/05 00:29:52 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_shell *general)
{
	char	**new_args;
	int		i;

	i = 1;
	new_args = general->cmd_lst->args;
	if (!new_args[1])
		return (EXIT_SUCCESS);
	while (new_args[i])
	{
		if (is_key_valid(general, new_args[i]))
			return (EXIT_SUCCESS);
		else
			return (unset_exp_var(general->sorted_env_lst, new_args[i]),
				unset_exp_var(general->env_lst, new_args[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_key_valid(t_shell *general, char *key)
{
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (EXIT_SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE_EXIT);
}

int	unset_exp_var(t_env *lst, char *n_new)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, n_new) == 0)
		{
			delete_exp_node(&lst, tmp);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	delete_exp_node(t_env **lst, t_env *nodik)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = *lst;
	if (*lst == nodik)
	{
		tmp = (*lst)->next;
		free_node(*lst);
		return (EXIT_SUCCESS);
	}
	while (tmp)
	{
		if (tmp == nodik)
		{
			prev->next = tmp->next;
			free_node(tmp);
			return (EXIT_SUCCESS);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
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
