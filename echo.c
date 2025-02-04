/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:55:03 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 00:01:43 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == '-')
			return (0);
		else if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_builtin(char **args)
{
	int	i;
	int	line_flag;

	line_flag = 1;
	i = 0;
	if (args && args[i])
		i++;
	while (args && args[i] && has_n(args[i]))
	{
		line_flag = 0;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (line_flag)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

// int	echo_builtin(t_shell *general, t_cmd_lst *cmd)  //need argssssss
// {
// 	int i;
//     int j;
//     int line_flag;

//     i = 1;
//     j = 2;
//     line_flag = 0;
//     if (!cmd->args[i])
//         return (ft_putstr_fd("\n", 1), 0);
//     if (ft_strcmp(cmd->args[i], "-n") == 0)
//     {
//         while (cmd->args[i][j] == 'n')
//             j++;
//         line_flag = 1;
//     }
//     while (cmd->args && cmd->args[i])
//     {
//         ft_putstr_fd(cmd->args[i], 1);
//         i++;
//         if (cmd->args[i])
//             ft_putstr_fd(" ", 1);
//     }
//     if (line_flag == 0)
//     {    ft_putstr_fd("\n", 1);}
//     set_exit_status(SUCCESS_EXIT);
// 	return (SUCCESS_EXIT);
// }
