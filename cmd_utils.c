/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/09 14:29:43 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static int	count_mid_args(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start && start != end)
	{
		count++;
		start = start->next;
	}
	return (count);
}

// static void	fill_cmd_token(t_cmd_lst *new_cmd, t_token *cmd_start, int token_count)
// {
	// int		i;
	// t_token	*current_token;

	// i = 0;
	// current_token = cmd_start;
	// new_cmd->args = malloc(sizeof(char *) * (token_count + 1));
	// if (!new_cmd->args)
	// 	return ;
	// if (ft_strcmp(current_token->context, " ") == 0)
		// new_cmd->cmd = strdup(current_token->next->context);
	// else
		// new_cmd->cmd = strdup(current_token->context);
	// write(1, "#\n", 2);
// 	new_cmd->args[0] = strdup(current_token->context);
// 	current_token = cmd_start->next;
// 	while (i < token_count)
// 	{
// 		new_cmd->args[i] = strdup(current_token->context);
// 		printf("new_cmd->arg = %s[%d]\n", new_cmd->args[i], i);
// 		current_token = current_token->next;
// 		i++;
// 	}
// 	new_cmd->args[token_count] = NULL;
// }

static t_cmd_lst *create_cmd_lst(t_token *token_lst)
{
	t_cmd_lst *cmd_lst = NULL;
	t_cmd_lst *current_cmd = NULL;
	t_cmd_lst *new_cmd;
	t_token *start;
	int token_count;
	t_token	*current_token;
	int i;

	i = 1;
	while (token_lst)
	{
		new_cmd = malloc(sizeof(t_cmd_lst));
		if (!new_cmd)
			return (NULL);
		new_cmd->cmd = NULL;
		new_cmd->args = NULL;
		new_cmd->next = NULL;
		start = token_lst;
		while (token_lst && token_lst->type != 1)
			token_lst = token_lst->next;
		token_count = count_mid_args(start, token_lst);
		if (token_count > 0)
		{
			new_cmd->args = malloc(sizeof(char *) * (token_count + 1));
			if (!new_cmd->args)
				return (NULL);
			current_token = start;
			if (ft_strcmp(current_token->context, " ") == 0)
			{
				new_cmd->cmd = strdup(current_token->next->context);
				new_cmd->args[0] = strdup(current_token->next->context);
			}
			else
			{
				new_cmd->cmd = strdup(current_token->context);
				new_cmd->args[0] = strdup(current_token->context);
			}
			// printf("new_cmd->arg = %s[0]\n", new_cmd->args[0]);
			current_token = start->next;
			while (i < token_count)
			{
				new_cmd->args[i] = strdup(current_token->context);
				current_token = current_token->next;
				i++;
			}
			new_cmd->args[token_count] = NULL;
		// fill_cmd_token(new_cmd, cmd_start, token_count);
		}

		if (!cmd_lst)
			cmd_lst = new_cmd;
		else
			current_cmd->next = new_cmd;
		current_cmd = new_cmd;
		if (token_lst && token_lst->type == 1)
			token_lst = token_lst->next;
	}
	return (cmd_lst);
}

void	free_cmd_lst(t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*temp;
	int			i;

	i = 0;
	temp = NULL;
	while (cmd_lst)
	{
		temp = cmd_lst;
		free(temp->cmd);
		if (temp->args)
		{
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		free(temp);
		cmd_lst = cmd_lst->next;
	}
}

void lalala(t_shell *general)
{
	// t_cmd_lst *commands = NULL;
	general->cmd_lst = create_cmd_lst(general->tok_lst);
	t_cmd_lst *temp = general->cmd_lst;
	while (temp) {
		printf("Command: %s\n", temp->cmd);
		printf("Arguments:");
		for (int i = 0; temp->args[i]; i++) {
			printf("%s ", temp->args[i]);
		}
		printf("\n\n");
		temp = temp->next;
	}
	// free_cmd_lst(commands);
	// print_tokens(general -> tok_lst);
}






// int	exchange_to_cmd(t_shell *general)
// {
//     t_token     *tmp_tok;
//     t_cmd_lst   *tmp;
//     t_cmd_lst   *head;

//     tmp = general->cmd_list;
//     head = general->cmd_list;
//     while (general->tok_lst)
//     {
//         tmp_tok = general->tok_lst;
//         general-> args_count = counter_args(general);
//         // if (general-> args_count < 0) // -2 error
//         // printf("dddd = %d, %s\n", general->args_count, general->tok_lst->context);
//         // general->cmd_list->args = (char **)malloc(sizeof(char *) * (general->args_count + 1));
//         // ete tesav nshana kanchum a funckia ov cmd sarqi, sarqeluc heto pointery araj a talis
//     }
//     return (0);
// }

// int counter_args(t_shell *general)
// {
//     general->args_count = 0;
//     while (general->tok_lst)
//     {
//         if (general->tok_lst->type != 0)
//             return (general-> args_count);
//         general-> args_count++;
//         general->tok_lst = general->tok_lst->next;
//     }
//     return (0);
// }