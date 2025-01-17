/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:45:04 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/16 21:46:05 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *init_env_nodes(char **env)
{
	t_env	*list_env;
	t_env	*tmp;
	t_env	*new_node;
	int		i;

	i = 0;
	list_env = NULL;
	tmp = NULL;
	while (env[i] != NULL)
	{
		new_node = ft_lstnew(env[i], 1);
		if (!new_node) 
			return NULL;
		if (list_env == NULL)
		{
			list_env = new_node;
			tmp = list_env;
		}
		else
			ft_lstadd_back(tmp, new_node);
		i++;
	}
	return (list_env);
}

t_env *add_env_dol(t_shell *general, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp_env;

	tmp_env = general->env_lst;
	new_node = spec_lstnew(key, value, 0);
	if (!new_node) 
		return NULL;
	ft_lstadd_back(general->env_lst, new_node);
	return (tmp_env);
}
int	create_env(char **env, t_shell *general)
{
	char	**sorted;

	general -> env_lst = init_env_nodes(env);
	sorted = sort_env(env);
	general -> env_lst = add_env_dol(general, "$", general->name);
	// ($?) Expands to the exit status of the most recently executed foreground pipeline.
	general -> env_lst = add_env_dol(general, "?", "0");
	general -> env_lst = add_env_dol(general, "0", "minishell");
	general -> sorted_env_lst = init_env_nodes(sorted);
	return (0);
}