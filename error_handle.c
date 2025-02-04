/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:16:41 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/02 01:28:57 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
}

void	check_malloc(t_shell *general, void *block)
{
	if (!block)
	{
		write(2, "Malloc Error\n", 13);
		clean_gen_exit(general, EXIT_FAILURE, 0, 1);
		exit(EXIT_FAILURE);
	}
}

void	my_error(char *cmd, char *error, int status)
{
	set_exit_status(status);
	ft_putstr_fd("minisHell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	mini_error(char *error, int fd)
{
	ft_putstr_fd("minisHell: ", fd);
	ft_putstr_fd(error, fd);
	ft_putstr_fd(": command not found\n", fd);
}

void	export_error(int status, char *cmd, char *msg)
{
	set_exit_status(status);
	ft_putstr_fd("minisHell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

// void	error_handle(void)
// {
// 	write(2, "Error\n", 6);
// 	exit(EXIT_FAILURE);
// }