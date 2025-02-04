/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:32:38 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 18:22:14 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env_nodes(char **env)
{
	int		i;
	t_env	*list_env;
	t_env	*tmp;
	t_env	*new_node;

	i = 0;
	list_env = NULL;
	tmp = NULL;
	while (env[i] != NULL)
	{
		new_node = ft_lstnew(env[i], 1);
		if (!new_node)
			return (NULL);
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

int	create_env(char **env, t_shell *general)
{
	char	**sorted;

	general -> env_lst = init_env_nodes(env);
	sorted = sort_env(env);
	general -> sorted_env_lst = init_env_nodes(sorted);
	free_array(sorted);
	sorted = NULL;
	return (0);
}

void	print_env(t_env *n_new, int flag)
{
	t_env	*lst;

	lst = bubble_sort_lst(n_new);
	while (lst != NULL)
	{
		if (flag == 1)
		{
			if (lst -> value == NULL)
				printf("declare -x %s\n", lst -> key);
			else
				printf("declare -x %s=\"%s\"\n", lst -> key, lst -> value);
		}
		else
		{
			if (lst -> value == NULL)
				printf("%s\n", lst -> key);
			else
				printf("%s=%s\n", lst -> key, lst -> value);
		}
		lst = lst->next;
	}
}

int	put_key(t_env *node, char	*src)
{
	int	j;

	j = 0;
	while (src[j] && src[j] != '=')
		j++;
	node -> key = (char *)malloc(sizeof(char) * (j + 1));
	if (!node-> key)
		return (-1);
	ft_strlcpy(node -> key, (const char *)src, j, 0);
	if (!node-> key)
		return (-1);
	return (j + 1);
}

void	put_value(t_env *node, char *src, int pos)
{
	int	len;

	(void)node;
	if (ft_strcmp(node->key, "OLDPWD") == 0)
	{
		node->value = NULL;
		return ;
	}
	len = sgmnt_len((const char *)src, pos);
	if (len == -1)
		return ;
	node -> value = (char *)malloc(sizeof(char) * (len + 1));
	if (!node -> value)
		return ;
	ft_strlcpy_2(node -> value, src, len, pos);
	if (!node -> value)
		return ;
}
