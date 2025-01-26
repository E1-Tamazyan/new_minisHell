/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/26 18:42:43 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 10 functions 🤯🤯🤯
// 10 functions 🤯🤯🤯
// 10 functions 🤯🤯🤯


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

void fill_commands(t_shell *general)
{
	t_token	*temp;
	int count;

	count = 0;
	if (general->curr_tok->type == WORD)
		general->curr_cmd->cmd = ft_strdup(general->curr_tok->context);
	temp = general->curr_tok;
	while (temp && temp->type == WORD && ++count)
		temp = temp->next;
	// printf("====>%d<======\n", count);
	if (count > 0)
	{
		general->curr_cmd->args = (char **)malloc(sizeof(char *) * (count + 1));
		if (!general->curr_cmd->args)
			return ;
		general->curr_cmd->args[count] = NULL;
	}	
}

int check_fill_commands(t_shell *g, int i, int j)
{
	while (g->curr_tok && i < g->pipe_count + 1)
	{
		if (g->curr_tok->type == PIPE)
		{
			g->curr_tok = g->curr_tok->next;
			continue ;
		}
		fill_commands(g);
		j = 0;
		while (g->curr_tok && g->curr_tok->type == WORD)
		{
			g->curr_cmd->args[j] = ft_strdup(g->curr_tok->context);
			g->curr_tok = g->curr_tok ->next;
			j++;
		}
		if (g->curr_tok)
			g->curr_tok = g->curr_tok->next;
		if (g->curr_cmd->next)
			g->curr_cmd = g->curr_cmd->next;
		else
			g->curr_cmd->next = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}
int create_cmd_lst(t_shell *g) // curr_cmd printable
{
	t_cmd_lst	*new;
	int			i;

	g->pipe_count = count_commands(g->tok_lst) - 1;
	printf("%d\n", g->pipe_count);
	i = 0;
	g->cmd_lst = initialize_new_cmd();
	while (i < g->pipe_count)
	{
		new = initialize_new_cmd();
		check_malloc(g->cmd_lst);
		list_add_back_cmd(&g->cmd_lst, new);
		i++;
	}
	redirs_management(g);
	// // 	g->tok_lst = skip_tokens(g->tok_lst);
	g->curr_cmd = g->cmd_lst;
	g->curr_tok = g->tok_lst;
	if (!g->curr_tok)
		return (EXIT_SUCCESS); // Exit_success
	return (check_fill_commands(g, 0, 0));
}

