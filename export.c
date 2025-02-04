/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:35:06 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 05:07:31 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_export_args(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (tmp_cmd_lst->args[j])
	{
		if (export_valid(tmp_cmd_lst->args[j]) == FAILURE_EXIT)
		{
			if (!tmp_cmd_lst->args[j + 1])
				return (export_error(FAILURE_EXIT, "export",
						tmp_cmd_lst->args[j]), FAILURE_EXIT);
			else
				j++;
		}
		if (ft_strchr(tmp_cmd_lst->args[j], '=') >= 0)
		{
			i = ft_strchr(tmp_cmd_lst->args[j], '=');
			add_env_lst_var(tmp_cmd_lst->args[j], general, i);
		}
		else
			add_env_no_var(tmp_cmd_lst->args[j], general);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	if (ft_strcmp(tmp_cmd_lst->cmd, "env") == 0 && !tmp_cmd_lst->args[1])
		return (print_env(general->sorted_env_lst, 0), EXIT_SUCCESS);
	if (ft_strcmp(tmp_cmd_lst->cmd, "export") == 0 && !tmp_cmd_lst->args[1])
		return (print_env(general->env_lst, 1), EXIT_SUCCESS);
	return (process_export_args(general, tmp_cmd_lst));
}

int	export_valid(char *arg)
{
	int	i;

	if (!arg)
		return (EXIT_FAILURE);
	if (arg[0] && !ft_isalpha(arg[0]) && arg[0] != '_')
		return (EXIT_FAILURE);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

t_env	**add_env_no_var(char *context, t_shell *general)
{
	t_env	*lol;
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, context) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			return (NULL);
		}
		tmp = tmp->next;
	}
	lol = my_lstnew(context, NULL);
	if (!lol)
		return (NULL);
	ft_lstadd_back(general->env_lst, lol);
	return (EXIT_SUCCESS);
}

t_env	**add_env_lst_var(char *context, t_shell *general, int i)
{
	char	*val;
	char	*key;
	t_env	*tmp;
	t_env	*lol;

	tmp = general->env_lst;
	key = my_substr(context, 0, i);
	val = my_substr(context, i + 1, ft_strlen(context) - i);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(val);
			lol = my_lstnew(key, val);
			return (NULL);
		}
		tmp = tmp->next;
	}
	lol = my_lstnew(key, val);
	if (!lol)
		return (NULL);
	ft_lstadd_back(general->env_lst, lol);
	ft_lstadd_back(general->sorted_env_lst, lol);
	return (EXIT_SUCCESS);
}
