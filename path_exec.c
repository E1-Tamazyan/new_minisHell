/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 00:52:54 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 05:28:55 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exec_error(t_shell *general, char *msg, int ex, int flag)
{
	my_error(NULL, msg, ex);
	clean_gen_exit(general, ex, 1, flag);
}

static void	check_and_execute(t_shell *general)
{
	if (access(general->cmd_lst->cmd, F_OK) == 0)
	{
		if (access(general->cmd_lst->cmd, X_OK) == 0)
		{
			if (execve(general->cmd_lst->cmd, general->cmd_lst->args,
					list_to_array(general->sorted_env_lst)) == -1)
				handle_exec_error(general, "No such file or directory", 127, 1);
		}
		else
			handle_exec_error(general, "Permission denied", 126, 1);
	}
	else
		handle_exec_error(general, "No such file or directory", 127, 1);
}

void	do_path_exec(t_shell *general)
{
	if (is_directory(general->cmd_lst->cmd))
	{
		handle_exec_error(general, "Is a directory", 126, 1);
	}
	check_and_execute(general);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}
