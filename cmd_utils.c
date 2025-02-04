/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/01 23:50:35 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_token *token)
{
	t_token	*temp;
	int		num;

	num = 1;
	temp = token;
	while (temp)
	{
		if (temp->type == 1)
			num++;
		temp = temp->next;
	}
	return (num);
}

int	is_redir(t_ttype type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT)
		return (1);
	return (0);
}

void	fill_commands(t_shell *general)
{
	t_token	*temp;
	int		count;

	count = 0;
	if (general->curr_tok->type == WORD)
		general->curr_cmd->cmd = ft_strdup(general->curr_tok->context);
	else if (is_redir(general->curr_tok->type))
		general->curr_cmd->cmd = NULL;
	temp = general->curr_tok;
	while (temp && temp->type == WORD && ++count)
		temp = temp->next;
}
