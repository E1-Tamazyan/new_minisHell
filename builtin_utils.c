/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:30:40 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 03:14:32 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char	*get_value(t_shell *general, char *keyik)
{
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, keyik) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	count_lst_len(t_env *env_lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**list_to_array(t_env *env)
{
	int		i;
	int		len;
	char	*tmp;
	char	**str;
	t_env	*env_temp;

	len = count_lst_len(env);
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	env_temp = env;
	while (env_temp)
	{
		tmp = str_join(env_temp->key, "=");
		str[i] = str_join(tmp, env_temp->value);
		free_set_null(tmp);
		if (!str[i])
			return (free_array(str), NULL);
		i++;
		env_temp = env_temp->next;
	}
	str[i] = NULL;
	return (str);
}
