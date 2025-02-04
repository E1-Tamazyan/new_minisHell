/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:09:11 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/04 19:35:22 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(t_shell *general)
{
	if (general->pipe_count > 0)
	{
		free(general->fd);
		general->fd = NULL;
	}
}

void	free_set_null(void *tmp)
{
	free(tmp);
	tmp = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	cmd_free(t_shell *general)
{
	if (general->cmd_lst)
	{
		free_cmd_lst(general->cmd_lst);
		general->cmd_lst = NULL;
	}
	else
		return ;
}
