/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:25:43 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 01:02:52 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	set_exit_status(int status)
{
	g_exit_status = status;
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

void	execution(t_shell *general, int index)
{
	int			i;
	t_cmd_lst	*new;
	t_cmd_lst	*tmp_cmd_lst;

	new = general->cmd_lst;
	tmp_cmd_lst = general->cmd_lst;
	if (general->cmd_lst == NULL)
		return ;
	if (general->pipe_count > 0)
	{
		index = pipe_fork(general, tmp_cmd_lst, index);
		i = 0;
		while (i < index && new)
		{
			waiting(new->pid, &g_exit_status);
			new = new->next;
			i++;
		}
	}
	else
		set_exit_status(exec_one_cmd(general, tmp_cmd_lst));
}

int	execute(t_shell *general, t_cmd_lst *tmp_cmd_lst, int index)
{
	init_signal(2);
	tmp_cmd_lst->pid = fork();
	if (tmp_cmd_lst->pid == 0)
	{
		duping(general, index);
		if (redir_dups(tmp_cmd_lst) < 0)
			clean_gen_exit(general, get_exit_status(), 1, 1);
		if (tmp_cmd_lst->cmd && is_builtin(tmp_cmd_lst->cmd))
		{
			do_builtin(general, tmp_cmd_lst);
			clean_gen_exit(general, get_exit_status(), 1, 1);
		}
		set_exit_status(exec_external_cmds(general, tmp_cmd_lst));
	}
	if (index > 0)
		close(general->fd[index - 1][0]);
	if (index < general->pipe_count)
		close(general->fd[index][1]);
	return (EXIT_SUCCESS);
}

int	exec_external_cmds(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	if (!tmp_cmd_lst->cmd)
		clean_gen_exit(general, get_exit_status(), 0, 1);
	if (is_abs_rel_path(tmp_cmd_lst->cmd))
		do_path_exec(general);
	else
	{
		split_and_run(general, tmp_cmd_lst);
		return (get_exit_status());
	}
	return (get_exit_status());
}

// void	do_path_exec(t_shell *general)
// {
// 	if (is_directory(general->cmd_lst->cmd))
// 	{
// 		my_error(NULL, "Is a directory", 126);
// 		clean_gen_exit(general, 126, 1, 1);
// 	}
// 	if (access(general->cmd_lst->cmd, F_OK) == 0)
// 	{
// 		if (access(general->cmd_lst->cmd, X_OK) == 0)
// 		{
// 			if (execve(general->cmd_lst->cmd, general->cmd_lst->args,
// 					list_to_array(general->sorted_env_lst)) == -1)
// 			{
// 				my_error(NULL, "No such file or directory", 127);
// 				clean_gen_exit(general, 127, 1, 1);
// 			}
// 		}
// 		else
// 		{
// 			my_error(NULL, "Permission denied", 126);
// 			clean_gen_exit(general, 126, 1, 0);
// 		}
// 	}
// 	else
// 	{
// 		my_error(NULL, "No such file or directory", 127);
// 		clean_gen_exit(general, 127, 1, 1);
// 	}
// }
