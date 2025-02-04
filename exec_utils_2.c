/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:07:27 by tumolabs          #+#    #+#             */
/*   Updated: 2025/02/02 14:06:25 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exit(t_shell *general)
{
	write(2, "Dup Error\n", 10);
	close_pipes(general->fd, general->pipe_count);
	clean_gen_exit(general, 1, 0, 1);
}

int	is_abs_rel_path(char *cmd)
{
	if (cmd[0] == '.' || (cmd[0] == '.' && cmd[1] == '/')
		|| (cmd[0] == '.' && cmd[1] == '.'
			&& cmd[2] == '/') || cmd[0] == '/' || cmd[0] == '~')
		return (1);
	return (0);
}

char	*the_path(char **splitted, char *cmd)
{
	char	*joined;
	char	**tmp;
	char	*temp;

	tmp = splitted;
	while (*tmp)
	{
		temp = ft_strjoin(*tmp, "/");
		joined = ft_strjoin(temp, cmd);
		free_set_null(temp);
		if (access(joined, F_OK) == 0)
		{
			return (joined);
		}
		free(joined);
		tmp++;
	}
	return (NULL);
}

void	clean_gen_exit(t_shell *general, int number, int cmd, int exitik)
{
	set_exit_status(number);
	if (cmd == 1)
	{
		free_cmd_lst(general->cmd_lst);
		general->cmd_lst = NULL;
	}
	free(general->doll_lst);
	general->doll_lst = NULL;
	free_env_lst(general->env_lst);
	free_env_lst(general->sorted_env_lst);
	close(general->original_stdin);
	close(general->original_stdout);
	free_fd(general);
	general->env_lst = NULL;
	general->sorted_env_lst = NULL;
	free(general);
	if (exitik == 1)
		exit(number);
}
