/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:00:31 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 01:03:02 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duping(t_shell *general, int index)
{
	if (index == 0)
	{
		if (dup2(general->fd[0][1], STDOUT_FILENO) == -1)
			close_exit(general);
	}
	else if (index == general->pipe_count)
	{
		if (dup2(general->fd[index - 1][0], STDIN_FILENO) == -1)
			close_exit(general);
	}
	else
	{
		if (dup2(general->fd[index][1], STDOUT_FILENO) == -1)
			close_exit(general);
		if (dup2(general->fd[index - 1][0], STDIN_FILENO) == -1)
			close_exit(general);
	}
	close_pipes(general->fd, general->pipe_count);
	return ;
}

int	exec_one_cmd(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	int	status;

	if (tmp_cmd_lst->cmd && is_builtin(tmp_cmd_lst->cmd))
	{
		redir_dups(tmp_cmd_lst);
		do_builtin(general, tmp_cmd_lst);
		dup2(general -> original_stdin, STDIN_FILENO);
		dup2(general -> original_stdout, STDOUT_FILENO);
	}
	else
	{
		init_signal(2);
		general->cmd_lst->pid = fork();
		if (general->cmd_lst->pid == 0)
		{
			if (redir_dups(tmp_cmd_lst) >= 0)
				set_exit_status(exec_external_cmds(general, general->cmd_lst));
			clean_gen_exit(general, get_exit_status(), 1, 1);
		}
		else if (general->cmd_lst->pid > 0)
			waiting(general->cmd_lst->pid, &status);
		else
			perror("fork");
	}
	return (get_exit_status());
}

void	do_builtin(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	(void)tmp_cmd_lst;
	if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "export") == 0)
		set_exit_status(export_builtin(general, tmp_cmd_lst));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "env") == 0)
		set_exit_status(export_builtin(general, tmp_cmd_lst));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "cd") == 0)
		set_exit_status(cd_builtin(general, tmp_cmd_lst));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "unset") == 0)
		set_exit_status(unset_builtin(general));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "exit") == 0)
		set_exit_status(exit_builtin(general));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "pwd") == 0)
		set_exit_status(pwd_builtin(general));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "echo") == 0)
		set_exit_status(echo_builtin(tmp_cmd_lst->args));
}

void	split_and_run(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	char	*path;
	char	**env;
	char	**splitted;

	path = getenv("PATH");
	splitted = ft_split(path, ':');
	path = the_path(splitted, tmp_cmd_lst->cmd);
	free_array(splitted);
	if (path == NULL)
	{
		my_error(tmp_cmd_lst->cmd, "command not found", 127);
		free_set_null(path);
		clean_gen_exit(general, 127, 1, 1);
	}
	env = list_to_array(general->sorted_env_lst);
	execve(path, tmp_cmd_lst->args, env);
	free_array(env);
	env = NULL;
	free_set_null(path);
}
