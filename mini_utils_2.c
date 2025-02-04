/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:02:16 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/04 23:03:42 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_input_validation(t_shell *g, char *input, int *i)
{
	skip_whitespace(input, i);
	if (check_inp_quotes(g, input, *i) == -1)
		return (-1);
	return (0);
}

int	check_flag_incr_input(t_shell *g, char *input, int *i, int flag)
{
	if (flag < 0)
		return (clean_list(&g->tok_lst), -1);
	if (input[*i])
		(*i)++;
	return (0);
}
