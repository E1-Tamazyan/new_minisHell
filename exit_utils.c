/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:27:06 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/08 22:30:51 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (FAILURE_EXIT);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (FAILURE_EXIT);
	while (str[i])
	{
		// printf("________________\n");
		// printf("%c\n", str[i]);
		if (str[i] < '0' || str[i] > '9')
			return (FAILURE_EXIT);
		i++;
	}
	return (SUCCESS_EXIT);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
	{
		count++;
	}
	return (count);
}

int	is_valid(char **args, int count)
{
	if (!args)
		return (FAILURE_EXIT);
	if (count > 1 && is_num(args[2]) == FAILURE_EXIT)
	{
		write(1, "$\n", 2);
		printf("minishell: exit: %s: numeric argument required", args[1]);
		return (FAILURE_EXIT);
	}
	if (count > 1 && ft_strlen(args[1]) > 20)
	{
		printf("minishell: exit: %s: numeric argument required", args[1]);
		return (FAILURE_EXIT);
	}
	return (SUCCESS_EXIT);
}

long	ft_atol(char *str)
{
	int		sign;
	long	num;
	size_t	i;

	i = 0;
	sign = 1;
	num = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}
