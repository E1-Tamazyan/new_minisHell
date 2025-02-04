/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:33:37 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/05 00:07:02 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_shell *general, t_cmd_lst *temp_cmd_lst)
{
	int		status;
	char	*cwd;
	char	*newcwd;

	cwd = getcwd(NULL, 0);
	status = SUCCESS_EXIT;
	if (count_args(temp_cmd_lst->args) > 2)
		return (my_error("cd", "too many arguments",
				EXIT_FAILURE), EXIT_SUCCESS);
	if (!temp_cmd_lst->args[1])
		status = change_home(general);
	else if (temp_cmd_lst->args[1] \
		&& ft_strcmp(temp_cmd_lst->args[1], "-") == 0)
		status = change_prev_dir(general);
	else if (temp_cmd_lst->args[1])
		status = change_dir(temp_cmd_lst->args[1]);
	newcwd = getcwd(NULL, 0);
	if (!newcwd)
		return (free_set_null(cwd), FAILURE_EXIT);
	change_env_value(general->env_lst, "PWD", newcwd);
	change_env_value(general->sorted_env_lst, "PWD", newcwd);
	change_env_value(general->env_lst, "OLDPWD", cwd);
	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
	free_set_null(cwd);
	return (status);
}

int	change_dir(char *dir)
{
	int	status;

	status = chdir(dir);
	if (status != 0)
	{
		write(2, "cd: ", 4);
		write(2, dir, ft_strlen(dir));
		write(2, ": No such file or directory\n", 28);
		return (FAILURE_EXIT);
	}
	return (EXIT_SUCCESS);
}

int	change_home(t_shell *general)
{
	char	*home;

	home = get_value(general, "HOME");
	if (!home)
		return (write(STDERR_FILENO, "HOME is not set",
				ft_strlen("HOME is not set")));
	else if (chdir(home) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		return (errno);
	}
	return (EXIT_SUCCESS);
}

int	change_prev_dir(t_shell *general)
{
	char	*prev;
	char	*msg;

	prev = get_value(general, "OLDPWD");
	if (!prev)
		return (ft_putstr_fd("minisHell: cd: OLDPWD not set\n", 2),
			FAILURE_EXIT);
	else if (chdir(prev) < 0)
	{
		msg = strerror(errno);
		return (write(STDERR_FILENO, msg, ft_strlen(msg)), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	change_env_value(t_env *lst, char *keyik, char *valik)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, keyik) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(valik);
			if (!tmp->value)
				return (FAILURE_EXIT);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
