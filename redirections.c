/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:20:21 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/25 14:49:45 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// smthhhhh
// int	open_file_and_remove_token(t_data *data)
// {
// 	int	status;

// 	status = 0;
// 	if (ft_strcmp(data->current->original_content, ">>") == 0)
// 	{
// 		data->current = ft_lst_delone(&data->tokens, data->current);
// 		data->curr_cmd->stdout = open_outfile(data,
// 				data->current->original_content, 1);
// 		if (data->curr_cmd->stdout == -1)
// 			return (data->curr_cmd->error = get_error_message(data),
// 				EXIT_FAILURE);
// 	}
// 	else if (data->current->original_content[0] == '>')
// 	{
// 		data->current = ft_lst_delone(&data->tokens, data->current);
// 		data->curr_cmd->stdout = open_outfile(data,
// 				data->current->original_content, 0);
// 		if (data->curr_cmd->stdout == -1)
// 			return (data->curr_cmd->error = get_error_message(data),
// 				EXIT_FAILURE);
// 	}
// 	else
// 		status = open_file_and_remove_token_2(data);
// 	data->current = ft_lst_delone(&data->tokens, data->current);
// 	return (status);
// }

// static catch_redir(t_shell *g)
// {

// }
// int	manage_redirs(t_shell *g, t_token	*tok)
// {
	// t_token	*temp;

	// temp = g->tok_lst;
	// while(temp)
	// {
	// 	if ((temp->type == 2 || temp->type == 3 
	// 		|| temp->type == 4 || temp->type == 5) 
	// 		&& (temp->next && temp->next->type == 0))
	// 	{
	// 		printf("hasaaav\n\n");
	// 		if (catch_redir(g) == -1)
	// 			return (EXIT_FAILURE);
	// 	}
	// 	temp = temp->next;
	// }
	// return (0);
	// // ********************************************************************
	// t_token *temp;

	// temp = g->tok_lst;
	// while (g->tok_lst)
	// {
	// 	if (g->tok_lst && g->tok_lst->type == 3 && 
	// 	((!g->tok_lst->next) || g->tok_lst->next->type == 1))
	// 		return (printf("minisHell: syntax error near unexpected token `|'"), -1);
	// 	else if (g->tok_lst->type == 2 || g->tok_lst->type == 3 
	// 	|| g->tok_lst->type == 4 || g->tok_lst->type == 5)
		
	// 	if (g->tok_lst)
	// 		g->tok_lst = g->tok_lst->next;
	// 	else
	// 		break;
	// }
// }