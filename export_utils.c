/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:14:30 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/04 23:56:01 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;
	char	*key_dup;
	char	*val_dup;

	key_dup = ft_strdup(key);
	if (!key_dup)
		return (NULL);
	if (value)
		val_dup = ft_strdup(value);
	else
		val_dup = NULL;
	if (value && !val_dup)
	{
		free(key_dup);
		return (NULL);
	}
	node = my_lstnew(key_dup, val_dup);
	if (!node)
	{
		free(key_dup);
		free(val_dup);
		return (NULL);
	}
	return (node);
}

int	update_existing_env(t_env *env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_to_env_lists(t_shell *general, char *key, char *value)
{
	t_env	*env_node;
	t_env	*sorted_node;

	if (update_existing_env(general->sorted_env_lst, key, value)
		&& update_existing_env(general->env_lst, key, value))
		return (EXIT_SUCCESS);
	env_node = create_env_node(key, value);
	if (!env_node)
		return (EXIT_FAILURE);
	sorted_node = create_env_node(key, value);
	if (!sorted_node)
	{
		free(env_node->key);
		free(env_node->value);
		free(env_node);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(general->env_lst, env_node);
	ft_lstadd_back(general->sorted_env_lst, sorted_node);
	return (EXIT_SUCCESS);
}
