/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:33:37 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/11 10:35:48 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_shell *general)
{
	int	status;

	status = SUCCESS_EXIT;
	if (!general->cmd_lst->args[1])
		status = change_home(general);
	else if (general->tok_lst->next
		&& ft_strcmp(general->cmd_lst->args[1], "-") == 0)
		status = change_prev_dir(general);
	else if (general->tok_lst->next)
		status = change_dir(general, general->cmd_lst->args[1]);
	return (status);
}

int	change_dir(t_shell *general, char *dir)
{
	char	*cwd;
	char	*prev;
	int		status;

	cwd = getcwd(NULL, 0);
	status = chdir(dir);
	if (status != 0)
	{
		printf(" cd: %s: No such file or directory", dir);
		return (FAILURE_EXIT);
	}
	prev = getcwd(NULL, 0);
	change_env_value(general->env_lst, "PWD", prev);
	change_env_value(general->sorted_env_lst, "PWD", prev);
	change_env_value(general->env_lst, "OLDPWD", cwd);
	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
	return (SUCCESS_EXIT);
}

int	change_home(t_shell *general)
{
	char	*home;
	int		status;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	home = get_value(general, "HOME");
	status = chdir(home);
	if (status != 0)
	{
		printf(" cd: %s: No such file or directory", home);
		return (FAILURE_EXIT);
	}
	change_env_value(general->env_lst, "PWD", home);
	change_env_value(general->sorted_env_lst, "PWD", home);
	change_env_value(general->env_lst, "OLDPWD", cwd);
	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
	return (SUCCESS_EXIT);
}

int	change_prev_dir(t_shell *general)
{
	int		status;
	char	*cwd;
	char	*prev;

	cwd = getcwd(NULL, 0);
	prev = get_value(general, "OLDPWD");
	status = chdir(prev);
	if (!prev)
		return (printf("minisHell: cd: OLDPWD not set\n"), FAILURE_EXIT);
	if (status != 0)
	{
		free(cwd);
		printf(" cd: %s: No such file or directory", prev);
		return (FAILURE_EXIT);
	}
	// cwd = getcwd(NULL, 0);
	change_env_value(general->env_lst, "PWD", prev);
	change_env_value(general->sorted_env_lst, "PWD", prev);
	change_env_value(general->env_lst, "OLDPWD", cwd);
	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
	return (SUCCESS_EXIT);
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
			return (SUCCESS_EXIT);
		}
		tmp = tmp->next;
	}
	return (SUCCESS_EXIT);
} 
