/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/26 15:25:52 by elen_t13         ###   ########.fr       */
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

static t_cmd_lst	*initialize_new_cmd()
{
	t_cmd_lst	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd_lst));
	check_malloc(new_cmd);
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->std_in = -2;
	new_cmd->std_out = -2;
	return (new_cmd);
}
	// int	status;

	// status = 0;
	// if (ft_strcmp(data->current->original_content, ">>") == 0)
	// {
	// 	data->current = ft_lst_delone(&data->tokens, data->current);
	// 	data->curr_cmd->stdout = open_outfile(data,
	// 			data->current->original_content, 1);
	// 	if (data->curr_cmd->stdout == -1)
	// 		return (data->curr_cmd->error = get_error_message(data),
	// 			EXIT_FAILURE);
	// }
	// else if (data->current->original_content[0] == '>')
	// {
	// 	data->current = ft_lst_delone(&data->tokens, data->current);
	// 	data->curr_cmd->stdout = open_outfile(data,
	// 			data->current->original_content, 0);
	// 	if (data->curr_cmd->stdout == -1)
	// 		return (data->curr_cmd->error = get_error_message(data),
	// 			EXIT_FAILURE);
	// }
	// else
	// 	status = open_file_and_remove_token_2(data);
	// data->current = ft_lst_delone(&data->tokens, data->current);
	// return (status);
void	ft_remove_list(t_token *prev, t_token *current)
{
	if (prev)
		prev->next = current->next;
	if (current->context)
		free(current->context);
	free(current);
}

t_token	*ft_lst_delone(t_token **lst, t_token *node)
{
	t_token	*current;
	t_token	*prev;

	if (!lst || !*lst || !node)
		return (NULL);
	if (*lst == node)
	{
		current = (*lst)->next;
		free((*lst)->context);
		free(*lst);
		*lst = current;
		return (current);
	}
	prev = NULL;
	current = *lst;
	while (current && current != node)
	{
		prev = current;
		current = current->next;
	}
	if (current == node)
		ft_remove_list(prev, current);
	return (prev->next);
}

// static int open_redir_rm_node(t_shell *g, t_cmd_lst **cmd, t_token **tok)
// {
// 	(void)g;
// 	if (ft_strcmp((*tok)->context, ">>") == 0)
// 	{
// 		(*tok) = ft_lst_delone(&(g->tok_lst), (*tok));
// 	// 	(*tok)->stdout = open_redir_out(g,
// 	// 			data->current->original_content, 1);
// 	// 	if (data->curr_cmd->stdout == -1)
// 	// 		return (data->curr_cmd->error = get_error_message(data),
// 	// 			-1);
// 	}
// 	else if ((*tok)->context[0] == '>')
// 	{
// 		(*tok) = ft_lst_delone(&(g->tok_lst), (*tok));
// 	// 	(*tok)->stdout = open_redir_out(g,
// 	// 			data->current->original_content, 1);
// 	// 	if (data->curr_cmd->stdout == -1)
// 	// 		return (data->curr_cmd->error = get_error_message(data),
// 	// 			-1);
// 	}
// 	// else if ((*tok)->context[0] == '<' || (ft_strcmp((*tok)->context, "<<")))
// 		// call the function to handle thiss parrttt
// 	(void)cmd;
// 	printf("&&&&&&&&&&&&&&&\n");
// 	print_tokens(g->tok_lst); 
// 	printf("&&&&&&&&&&&&&&&\n");
// 	return (1);
// }
// here will be made only one node of cmdp
	// I am stuck hereee **************
// static int	fill_command_node(t_cmd_lst **cmd, t_token **token_lst, t_shell *g)
// {
// 	t_cmd_lst *cmd_curr = *cmd; 
// 	t_token *tok_curr = *token_lst; 
	
// 	(*cmd)->cmd = ft_strdup((*token_lst)->context);
// 	(*cmd)->args = NULL;
// 	while(cmd_curr && tok_curr)
// 	{
// 		if (cmd_curr && tok_curr
// 			&& (tok_curr->type == 2 || tok_curr->type == 5 
// 			|| tok_curr->type == 3 || tok_curr->type == 4)
// 			&& (tok_curr->next && tok_curr->next->type == 0))
// 		{
// 			if (open_redir_rm_node(g, &cmd_curr, &tok_curr) == -1
// 				&& g->pipe_count < 1)
// 				return (-1);
// 		}
// 		else if (tok_curr)
// 			tok_curr = tok_curr->next;
// 		else
// 			break ;
// 	}
// 	return (0);
// }

// static t_token	*skip_tokens(t_token *token_lst)
// {
// 	while (token_lst && token_lst->type != 1)
// 		token_lst = token_lst->next;
// 	if (token_lst && token_lst->type == 1)
// 		token_lst = token_lst->next;
// 	return (token_lst);
// }

void	list_add_back_cmd(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*add;

	add = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (add->next != NULL)
			add = add->next;
		add->next = new;
		new->next = NULL;
	}
}

// static void redirs_management(t_shell *g)
// {}

static void fill_commands(t_shell *general)
{
	t_token	*temp;
	int count;

	count = 0;
	if (general->curr_tok->type == WORD)
		general->curr_cmd->cmd = ft_strdup(general->curr_tok->context);
	temp = general->curr_tok;
	while (temp && temp->type == WORD && ++count)
	{
		printf("====>%d<======\n", count);	
		temp = temp->next;
	}
	if (count > 0)
	{
		general->curr_cmd->args = (char **)malloc(sizeof(char *) * (count + 1));
		if (!general->curr_cmd->args)
			return ;
		general->curr_cmd->args[count] = NULL;
	}	
}

static int check_fill_commands(t_shell *g, int i, int j)
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
		while(g->curr_tok && g->curr_tok == WORD)
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
int create_cmd_lst(t_shell *g)
{
	t_cmd_lst	*new;
	int			i;

	g->pipe_count = count_commands(g->tok_lst) - 1;
	g->curr_tok = g->tok_lst; // arzheqvorel chmoranal
	i = 0;
	(void)i;
	g->cmd_lst = initialize_new_cmd();
	while (i < g->pipe_count)
	{
		new = initialize_new_cmd();
		check_malloc(g->cmd_lst);
		list_add_back_cmd(&g->cmd_lst, new);
		i++;
	}
	// redirs_management(g);
	// // 	g->tok_lst = skip_tokens(g->tok_lst);
	g->curr_cmd = g->cmd_lst;
	g->curr_tok = g->tok_lst;
	if (!g->curr_tok)
		return (EXIT_SUCCESS); // Exit_success
	return (check_fill_commands(g, 0, 0));
}

