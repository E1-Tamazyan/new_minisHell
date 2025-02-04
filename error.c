/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 00:21:54 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 18:58:58 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	which_errno(void)
{
	if (errno == ENOENT)
		write(STDERR_FILENO, NO_SUCH_FILE_MSG, ft_strlen(NO_SUCH_FILE_MSG));
	else if (errno == EACCES)
		write(STDERR_FILENO, PERMISSION_DENIED_MSG,
			ft_strlen(PERMISSION_DENIED_MSG));
	else if (errno == EISDIR)
	{
		write(STDERR_FILENO, IS_DIRECTORY_MSG, ft_strlen(IS_DIRECTORY_MSG));
	}
	else if (errno == ENOTDIR)
		write(STDERR_FILENO, NOT_DIRECTORY_MSG, ft_strlen(NOT_DIRECTORY_MSG));
}

void	error_msg(int status, char *command_name)
{
	set_exit_status(status);
	if (command_name)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, command_name, ft_strlen(command_name));
		write(STDERR_FILENO, ": ", 2);
		which_errno();
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	syntax_error(char *message)
{
	char	*str;

	str = "syntax error near unexpected token `";
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "'\n", 2);
	set_exit_status(258);
	return ;
}

void	syntax_error_2(char c1, char c2)
{
	char	*str;

	str = "syntax error near unexpected token `";
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, &c1, 1);
	write(STDERR_FILENO, &c2, 1);
	write(STDERR_FILENO, "'\n", 2);
	set_exit_status(258);
	return ;
}
