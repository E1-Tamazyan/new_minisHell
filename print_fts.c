/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:39:24 by etamazya          #+#    #+#             */
/*   Updated: 2025/01/17 17:29:55 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printStrings(char **strs)
{
	int	i;

	i = 0;
	if (!strs) 
		return;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}
// 		// ***** just print *****
void	print_cmd(t_cmd_lst	*cmd_lst)
{
	t_cmd_lst *temp = cmd_lst;
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	while (temp)
	{
		// printf("dfsf\n");
		printf("Command: %s\n", temp->cmd);
		// printf("----------------\n");
		printf("Arguments:");
		for (int i = 0; temp->args[i]; i++)
			printf("%s ", temp->args[i]);
		printf("\n\n");
		temp = temp->next;
	}
}