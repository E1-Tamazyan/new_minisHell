/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:35:06 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/04 23:14:17 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_tmp_func(char *key, char *value)
{
	free(key);
	free(value);
	return (EXIT_FAILURE);
}

static int	process_env_arg(t_shell *general, char *arg)
{
	int		equal_pos;
	char	*key;
	char	*value;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos >= 0)
	{
		key = my_substr(arg, 0, equal_pos);
		if (!key)
			return (EXIT_FAILURE);
		value = my_substr(arg, equal_pos + 1, ft_strlen(arg) - (equal_pos + 1));
		if (!value)
		{
			free(key);
			return (EXIT_FAILURE);
		}
		if (add_to_env_lists(general, key, value) == EXIT_FAILURE)
			return (_tmp_func(key, value));
		_tmp_func(key, value);
	}
	else
		if (add_to_env_lists(general, arg, NULL) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	process_export_args(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	int	j;

	j = 1;
	while (tmp_cmd_lst->args[j])
	{
		if (export_valid(tmp_cmd_lst->args[j]) == FAILURE_EXIT)
		{
			if (!tmp_cmd_lst->args[j + 1])
				return (export_error(FAILURE_EXIT, "export",
						tmp_cmd_lst->args[j]), FAILURE_EXIT);
			j++;
			continue ;
		}
		if (process_env_arg(general, tmp_cmd_lst->args[j]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	if (ft_strcmp(tmp_cmd_lst->cmd, "env") == 0 && !tmp_cmd_lst->args[1])
		return (print_env(general->env_lst, 0), EXIT_SUCCESS);
	if (ft_strcmp(tmp_cmd_lst->cmd, "export") == 0 && !tmp_cmd_lst->args[1])
		return (print_env(general->sorted_env_lst, 1), EXIT_SUCCESS);
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
