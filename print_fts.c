/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:39:24 by etamazya          #+#    #+#             */
/*   Updated: 2025/01/26 17:03:09 by etamazya         ###   ########.fr       */
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
	t_cmd_lst *temp;
	
	temp = cmd_lst;
	printf("----\n");
	while (temp)
	{
		printf("Command: %s\n", temp->cmd);
		printf("Arguments:");
		int i = 0;
		while(temp->args && temp->args[i])
		{
			printf("%s ", temp->args[i]);
			i++;
		}
		// if(temp->args)
		// {	
		// for (int i = 0; temp->args[i]; i++)
			// printf("%s ", temp->args[i]);
		// }
		printf("\n");
		temp = temp->next;
	}
	printf("----\n");
}