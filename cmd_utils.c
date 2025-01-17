/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/17 19:58:07 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 8 functions 🤯🤯🤯
// 8 functions 🤯🤯🤯
// 8 functions 🤯🤯🤯

static t_cmd_lst *initialize_new_cmd()
{
	t_cmd_lst *new_cmd = malloc(sizeof(t_cmd_lst));
	check_malloc(new_cmd);
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	return new_cmd;
}

static void populate_command(t_cmd_lst *cmd, t_token *token_lst, int token_count)
{
	cmd->cmd = strdup(token_lst->context);
	cmd->args = malloc(sizeof(char *) * (token_count + 1));
	check_malloc(cmd->args);

	for (int i = 0; i < token_count; i++)
	{
		cmd->args[i] = strdup(token_lst->context);
		token_lst = token_lst->next;
	}
	cmd->args[token_count] = NULL;
}

static t_token *skip_tokens(t_token *token_lst)
{
	while (token_lst && token_lst->type != 1)
		token_lst = token_lst->next;
	if (token_lst && token_lst->type == 1)
		token_lst = token_lst->next;
	return token_lst;
}

// static t_cmd_lst *initialize_new_cmd()
// {
// 	t_cmd_lst *new_cmd;

// 	new_cmd = malloc(sizeof(t_cmd_lst));
// 	check_malloc(new_cmd);
// 	new_cmd->cmd = NULL;
// 	new_cmd->args = NULL;
// 	new_cmd->next = NULL;
// 	return (new_cmd);
// }

// static void populate_command(t_cmd_lst *cmd, t_token *token_lst, int token_count)
// {
// 	int	i;
// 	cmd->cmd = strdup(token_lst->context);
// 	cmd->args = malloc(sizeof(char *) * (token_count + 1));
// 	check_malloc(cmd->args);

// 	i = 0;
// 	while (i < token_count)
// 	{
// 		cmd->args[i] = strdup(token_lst->context);
// 		token_lst = token_lst->next;
// 		i++;
// 	}
// 	cmd->args[token_count] = NULL;
// }

// static t_token *skip_tokens(t_token *token_lst)
// {
// 	while (token_lst && token_lst->type != 1)
// 		token_lst = token_lst->next;
// 	if (token_lst && token_lst->type == 1)
// 		token_lst = token_lst->next;
// 	return (token_lst);
// }

t_cmd_lst *create_cmd_lst(t_token *token_lst)
{
	t_cmd_lst *cmd_lst = NULL;
	t_cmd_lst *current_cmd = NULL;
	t_cmd_lst *new_cmd;
	int token_count;

	while (token_lst)
	{
		new_cmd = initialize_new_cmd();
		token_count = count_tokens(token_lst);
		populate_command(new_cmd, token_lst, token_count);
		if (!cmd_lst)
			cmd_lst = new_cmd;
		else
			current_cmd->next = new_cmd;
		current_cmd = new_cmd;
		token_lst = skip_tokens(token_lst);
	}
	return (cmd_lst);
}
