/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:47:41 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/09 19:57:15 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status = 0;

void	set_exit_status(int status)
{
	exit_status = status;
}

int	get_exit_status(void)
{
	return (exit_status);
}

int	exit_statusik(char *arg)
{
	int		exit;
	long	num;

	if (arg)
	{
		num = ft_atol(arg);
		exit = num % 256;
		if (exit < 0)
			exit += 256;
		return (exit);
	}
	else
		return (exit_status);
}

int	exit_builtin(t_shell *general)
{
	int	exitik;
	int	count;

	count = count_args(general->cmd_lst->args);
	exitik = 255;
	write(2, "exit\n", 6);
	if (is_valid(general->cmd_lst->args, count) == FAILURE_EXIT)
		exit(exitik);
	if (count > 3)
		return (printf("minishell: exit: too many arguments\n"), FAILURE_EXIT);
	exitik = exit_statusik(general->cmd_lst->args[1]);
	// free_general(general);
	exit(exitik);
}
