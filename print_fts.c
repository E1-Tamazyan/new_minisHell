/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:39:24 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/08 12:43:41 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printStrings(char **strs)
{
	int i;

	i = 0;
    if (!strs) 
        return;
    while (strs[i] != NULL)
	{
        printf("%s\n", strs[i]);
		i++;
    }
}